![1686902795488](https://github.com/Leavaway/csnotes/assets/86211987/25c813e9-e0d7-4dec-912c-cb8c7385afda)
 
当一个函数参数是一个指针的指针(比如 pte_t **pte_store)时, 这通常意味着函数希望能够修改传入的指针, 为了让函数能够这样做,需要传递该指针的地址</br>
// can't use va+size as upper bound, may overflow</br>
	pages[0].pp_ref = 1;
 size_t i;
	for (i = 0; i < npages; i++) {
		if(i*PGSIZE>=IOPHYSMEM && i*PGSIZE<EXTPHYSMEM + (uint32_t)boot_alloc(0) - KERNBASE){
			pages[i].pp_ref = 1;
		}else{
			pages[i].pp_ref = 0;
		}
		pages[i].pp_link = page_free_list;
		page_free_list = &pages[i];
	}
	pages[0].pp_ref = 1;
 这段代码把所有页面都加进了page_free_list. 并且计算内核使用的物理内存范围的方式不正确

 碰到了 Kernel page directory: FAIL 
    AssertionError: ...
         check_page_alloc() succeeded!
         kernel panic at kern/pmap.c:810: assertion failed: check_va2pa(kern_pgdir, PGSIZE) == page2pa(pp2)
         Welcome to the JOS kernel monitor!
         Type 'help' for a list of commands.
         qemu: terminating on signal 15 from pid 10394
    MISSING 'check_kern_pgdir\(\) succeeded!'错误 显示是在kern/pmap.c:810: assertion failed: check_va2pa(kern_pgdir, PGSIZE) == page2pa(pp2) 有assert 错误
    在gdb里面用break kern/pmap.c:810调试并且打印kern_pgdir和pp2的值
    发现x /4x 0xf0122fe8 为0x00 0x00 0x00 0x00 应该是前面memset的正常值,
    可能是在尝试映射 pp2 的时候, 页面表项可能没有正确地分配或者访问, 检查 pgdir_walk 函数
    4030722052  4030722049
    pte_t *pte = KADDR(PTE_ADDR(*ptp_addr)) + PTX(va); -> pte_t *pte = KADDR(PTE_ADDR(*ptp_addr)); return &pte[PTX(va)];
    前面直接算得ptp_addr物理地址然后转换成了虚拟地址后直接加上了PTX(va)也就是页表条目index, 而不是地址上的偏移量, 后面使用的是数组索引，它实际上是在做指针算术, 会考虑到pte_t的大小
    查询pde_t * ptp_addr = pgdir + PDX(va); 和 pde_t * ptp_addr = &pgdir[PDX(va)];
    中print *pte_addr的值4190215   4190215
    当使用数组索引时，C语言会自动处理元素的大小，而当直接使用加法来移动指针时，需要手动考虑元素的大小。

	
    boot_map_region(kern_pgdir, KERNBASE, 0xffffffff - KERNBASE, 0, PTE_W | PTE_P); 
    DR0=00000000 DR1=00000000 DR2=00000000 DR3=00000000 
         DR6=ffff0ff0 DR7=00000400
         EFER=0000000000000000
         Triple fault.  Halting for inspection via QEMU monitor.
    这是因为 0xffffffff 是 32 位的最大无符号整数，所以 0xffffffff - KERNBASE 实际上是 2^32 - 1 - KERNBASE，少了一页。

    kernel panic at kern/pmap.c:722: assertion failed: check_va2pa(pgdir, KERNBASE + i) == i
    查看代码可推测应该是boot_map_region函数的问题, 其中一开始用va+size as upper bound作为上界可能会导致溢出, 考虑到目前没有64位unsigned int, 改用size/PGSIZE作为上界.
    

