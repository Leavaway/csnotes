## 锁

在多处理器环境中，如果一个处理器需要另一个处理器执行某项任务，它可以通过其本地APIC发送一个IPI（Inter-Processor Interrupt）给另一个处理器。在JOS中，lapic_ipi函数就是用来发送IPI的。

每个处理器都有自己的中断请求队列和调度器，可以独立于其他处理器处理中断和调度环境。这样的设计可以提高系统的并行性，但也带来了额外的同步挑战。为了防止数据竞争和不一致，可能需要使用锁等同步原语。在JOS中，kern/spinlock.c和kern/kclock.c就是用于处理这些问题的。

最后，关于多处理器环境的调度问题。在JOS中，每个处理器都运行自己的调度器，并独立于其他处理器选择要运行的环境。这意味着，在给定时刻，可能有多个环境同时运行，每个运行在不同的处理器上。然而，所有的处理器共享相同的环境列表，因此，为了避免并发冲突，必须在修改环境列表时采取适当的同步措施。


CR1, CR2 和 CR3 是 x86 架构下的控制寄存器（Control Registers）。他们用于存储和控制处理器的某些状态。下面是它们各自的用途：

CR0：此寄存器包含处理器的一些重要操作模式和状态。例如，它的最低位（PE，Protection Enable）决定了处理器是在实模式（real mode）下运行，还是在保护模式（protected mode）下运行。实模式是 x86 早期的操作模式，没有内存保护和多任务能力。而保护模式则拥有这些特性。另外，CR0 的 PG 位（Paging）用于开启或关闭分页。

CR2：此寄存器包含最后一次出现页面错误（Page Fault）的线性地址。也就是说，当一个程序试图访问一个没有映射，或者没有足够权限的内存地址时，处理器就会触发一个页面错误异常，同时，错误的地址被存储在 CR2 中，以便后续的错误处理。

CR3：此寄存器被用于分页系统。它存储了当前正在使用的页目录的物理地址。当一个程序访问内存时，处理器需要查找页表来确定虚拟地址对应的物理地址，这个查找过程就需要用到 CR3。此外，当 CR3 被写入新的值时，处理器会自动使所有已经缓存的页表条目失效，强制处理器在下一次内存访问时重新查找页表。


Qusetion 1：
　　 仔细比较kern/mpentry.S与boot/boot.S，想想kern/mpentry.S是被编译链接来运行在KERNBASE之上的，那么定义MPBOOTPHYS宏的目的是什么？为什么在kern/mpentry.S中是必要的，在boot/boot.S中不是呢？换句话说，如果我们在kern/mpentry.S中忽略它，会出现什么错误？
　　 回答：
　　 #define MPBOOTPHYS(s) ((s) - mpentry_start + MPENTRY_PADDR))))
　　 MPBOOTPHYS is to calculate symobl address relative to MPENTRY_PADDR. The ASM is executed in the load address above KERNBASE, but JOS need to run mp_main at 0x7000 address! Of course 0x7000’s page is reserved at pmap.c.
　　 在AP的保护模式打开之前，是没有办法寻址到3G以上的空间的，因此用MPBOOTPHYS是用来计算相应的物理地址的。
但是在boot.S中，由于尚没有启用分页机制，所以我们能够指定程序开始执行的地方以及程序加载的地址；但是，在mpentry.S的时候，由于主CPU已经处于保护模式下了，因此是不能直接指定物理地址的，给定线性地址，映射到相应的物理地址是允许的。
**Per-CPU State and Initialization
　　 当编写一个多进程OS时，这是非常重要的去区分哪些是每个进程私有的CPU状态，哪些是整个系统共享的全局状态。在kern/cpu.h中定义了大部分的per-CPU状态。
　　 每个CPU独有的变量应该有：

内核栈，因为不同的核可能同时进入到内核中执行，因此需要有不同的内核栈
TSS描述符
每个核的当前执行的任务
每个核的寄存器

加锁: 
In i386_init(), acquire the lock before the BSP wakes up the other CPUs.
In mp_main(), acquire the lock after initializing the AP, and then call sched_yield() to start running environments on this AP.
In trap(), acquire the lock when trapped from user mode. To determine whether a trap happened in user mode or in kernel mode, check the low bits of the tf_cs.
In env_run(), release the lock right before switching to user mode. Do not do that too early or too late, otherwise you will experience races or deadlocks.


lcr3(PADDR(curenv->env_pgdir));
unlock_kernel();
env_pop_tf(&curenv->env_tf);
lcr3(PADDR(curenv->env_pgdir)); 这一行是切换到新环境的地址空间，这个操作需要在大内核锁保护下进行，因为它涉及到修改处理器的控制寄存器，这是一个关键的系统级操作。
env_pop_tf(&curenv->env_tf); 这一行是恢复新环境的寄存器状态并将处理器从内核模式切换到用户模式。在这个操作之后，处理器将开始在新环境中运行用户代码，此时应该已经释放大内核锁，否则当其他处理器尝试进入内核模式时，将会被阻塞。
