用户环境的代码被调用前，操作系统一共按顺序执行了以下几个函数：

　　　　* start (kern/entry.S)

　　　　* i386_init (kern/init.c)

　　　　　　　cons_init

　　　　　　　mem_init

　　　　　　　env_init

　　　　　　　trap_init （目前还未实现）

　　　　   　　env_create

　　　　   　　env_run

　　　　　　　　env_pop_tf

TSS堆栈流程
![1687745994812](https://github.com/Leavaway/csnotes/assets/86211987/e580cc71-f7f1-46df-858b-05d819d21c37)

## bugs
	boot_map_region(kern_pgdir, UENVS, ROUNDUP(sizeof(struct Env)*NENV, PGSIZE), PADDR(envs), PTE_U|PTE_P);
 无法进入用户态
 boot_map_region(kern_pgdir, UENVS, ROUNDUP(sizeof(struct Env)*NENV, PGSIZE), PADDR(envs), PTE_U);

 改后可以进入但是还是无法正确处理T_DIVIDE, 是在load_icode的代码中漏掉了lcr3(PADDR(e->env_pgdir));
 lcr3()函数是用来加载页目录的。它将CR3寄存器的值设置为给定的物理地址，这个物理地址就是页目录的地址。CR3寄存器中存储的是当前活动的页目录的物理地址。
在原来的代码中，没有明确地使用lcr3()函数加载环境对应的页目录到CR3寄存器。这可能导致在加载程序到内存时，使用了错误的页目录。例如，它可能使用了内核的页目录kern_pgdir，而不是环境自己的页目录e->env_pgdir。


buggyhello: FAIL (2.2s) 
    AssertionError: ...
         Incoming TRAP frame at 0xefffffbc
         [00001000] user_mem_check assertion failure for va 00000000
    GOOD [00001000] free env 00001000
         Destroyed the only environment - nothing more to do!
         Welcome to the JOS kernel monitor!
         Type 'help' for a list of commands.
         qemu: terminating on signal 15 from pid 4761
    MISSING '.00001000. user_mem_check assertion failure for va 00000001'
    
    QEMU output saved to jos.out.buggyhello
检查user_mem_check函数，如果出现错误的页正好是整个检查范围的第一个页（即对 va 下取整的结果），那么应该返回原始的 va 而不是对齐后的 start，因为出错的实际地址可能就在这个页内，但是不一定在页的起始。举个例子，假设 va 是 0x1003，页大小 PGSIZE 是 0x1000。在页对齐后，start 会被设置为 0x1000。然后假设在 0x1000 到 0x2000 的这个页内发现了权限错误，那么错误的实际地址可能就是 0x1003，所以这个时候应该返回 va 而不是 start。但是如果错误发生在后续的页，比如 0x2000 到 0x3000，那么返回 start 是合适的，因为我们只知道错误发生在这个页内，但是不知道具体的地址。在特殊情况时候返回 start 仍然能够指出错误发生在哪个页内。然而，返回 va 可以给出更精确的错误位置。所以在这种情况需要单独检查一下va。
