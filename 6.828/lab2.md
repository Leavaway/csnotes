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
    发现x /4x 0xf0122fe8 为0x00 0x00 0x00 0x00 

