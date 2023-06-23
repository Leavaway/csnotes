![1686902795488](https://github.com/Leavaway/csnotes/assets/86211987/25c813e9-e0d7-4dec-912c-cb8c7385afda)
 
当一个函数参数是一个指针的指针(比如 pte_t **pte_store)时, 这通常意味着函数希望能够修改传入的指针, 为了让函数能够这样做,需要传递该指针的地址</br>
## 基础概念
va是一个虚拟地址, 因为在本节中没有启用上图中所示的分段机制, 所以va也等同于线性地址, 即可以通过分页机制查询得到物理地址。在程序中, ph->p_va 是这个段在虚拟内存空间中的起始地址。这是由链接器在编译时确定的。当编译一个程序时，链接器会根据一些规则(例如，特定的内存布局)，决定每个段应该被放在虚拟地址空间的什么位置。<br/>
page directory: 页目录, 维护页面索引信息, 可以通过pgdir基址＋偏移量得到页表项地址<br/>
page table entry: 页表项, 存储了页面物理地址和相关权限位<br/>
PageInfo 是用于管理物理页面的结构。通常，操作系统会为所有的物理内存页面维护一个 PageInfo 数组。这个数组通常位于内核的内存空间，并且在系统启动时由内核初始化。每个 PageInfo 结构通常对应于一个物理页面，并包含有关该页面的元信息（如引用计数，是否已分配等）。<br/>
初始化流程: i386_detect_memory(): 探测系统的物理内存，并设置npages和npages_basemem变量，这两个变量分别表示总的物理内存页数和基本内存（小于等于1MB）的页数。<br/>
随后通过boot_alloc()完成一些基本的初始化步骤(初始化页目录, 分配PageInfo数组等). <br/>
随后设置内核的虚拟内存映射：mem_init()函数中的boot_map_region()调用设置了内核的虚拟内存映射。包括以下几部分：pages数组映射到UPAGES，内核栈映射到KSTACKTOP，所有物理内存映射到KERNBASE。<br/>
更多相关宏定义 函数和介绍可以查看mmu.h pmap.h memlayout.h等文件<br/>

## bugs
 ```pages[0].pp_ref = 1;<br/>
 size_t i;<br/>
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
 ```
 这段代码把所有页面都加进了page_free_list. 并且计算内核使用的物理内存范围的方式不正确<br/>

 碰到了 Kernel page directory: FAIL <br/>
    AssertionError: ...<br/>
         check_page_alloc() succeeded!<br/>
         kernel panic at kern/pmap.c:810: assertion failed: check_va2pa(kern_pgdir, PGSIZE) == page2pa(pp2)<br/>
         Welcome to the JOS kernel monitor!<br/>
         Type 'help' for a list of commands.<br/>
         qemu: terminating on signal 15 from pid 10394<br/>
    MISSING 'check_kern_pgdir\(\) succeeded!'错误 显示是在kern/pmap.c:810: assertion failed: check_va2pa(kern_pgdir, PGSIZE) == page2pa(pp2) 有assert 错误<br/>
    在gdb里面用break kern/pmap.c:810调试并且打印kern_pgdir和pp2的值<br/>
    发现x /4x 0xf0122fe8 为0x00 0x00 0x00 0x00 应该是前面memset的正常值,<br/>
    可能是在尝试映射 pp2 的时候, 页面表项可能没有正确地分配或者访问, 检查 pgdir_walk 函数<br/>
    4030722052  4030722049<br/>
    pte_t *pte = KADDR(PTE_ADDR(*ptp_addr)) + PTX(va); -> pte_t *pte = KADDR(PTE_ADDR(*ptp_addr)); return &pte[PTX(va)];<br/>
    前面直接算得ptp_addr物理地址然后转换成了虚拟地址后直接加上了PTX(va)也就是页表条目index, 而不是地址上的偏移量, 后面使用的是数组索引，它实际上是在做指针算术, 会考虑到pte_t的大小<br/>
    查询pde_t * ptp_addr = pgdir + PDX(va); 和 pde_t * ptp_addr = &pgdir[PDX(va)];<br/>
    中print *pte_addr的值4190215   4190215<br/>
    当使用数组索引时，C语言会自动处理元素的大小，而当直接使用加法来移动指针时，需要手动考虑元素的大小。<br/>

	
    boot_map_region(kern_pgdir, KERNBASE, 0xffffffff - KERNBASE, 0, PTE_W | PTE_P); <br/>
    DR0=00000000 DR1=00000000 DR2=00000000 DR3=00000000 <br/>
         DR6=ffff0ff0 DR7=00000400<br/>
         EFER=0000000000000000<br/>
         Triple fault.  Halting for inspection via QEMU monitor.<br/>
    这是因为 0xffffffff 是 32 位的最大无符号整数，所以 0xffffffff - KERNBASE 实际上是 2^32 - 1 - KERNBASE，少了一页。<br/>

    kernel panic at kern/pmap.c:722: assertion failed: check_va2pa(pgdir, KERNBASE + i) == i<br/>
    查看代码可推测应该是boot_map_region函数的问题, debug得到一个va的值4009754624，已经比较接近32位unsigned int 最大值, 其中一开始用va+size as upper bound作为上界可能会导致溢出, 考虑到目前没有64位unsigned int, 改用size/PGSIZE作为上界.<br/>
    

