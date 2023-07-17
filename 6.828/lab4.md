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



6828 decimal is 15254 octal!
Physical memory: 131072K available, base = 640K, extended = 130432K
check_page_free_list() succeeded!
check_page_alloc() succeeded!
check_page() succeeded!
check_kern_pgdir() succeeded!
check_page_free_list() succeeded!
check_page_installed_pgdir() succeeded!
SMP: CPU 0 found 1 CPU(s)
EAX=00000010 EBX=00000048 ECX=00000001 EDX=00000000
ESI=f0104984 EDI=f0105efc EBP=f0104978 ESP=efff8004
EIP=3a0946d5 EFL=00000046 [---Z-P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
CS =0008 00000000 ffffffff 00cf9a00 DPL=0 CS32 [-R-]
SS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
DS =0010 00000000 ffffffff 00cf9300 DPL=0 DS   [-WA]
FS =0023 00000000 ffffffff 00cff300 DPL=3 DS   [-WA]
GS =0023 00000000 ffffffff 00cff300 DPL=3 DS   [-WA]
LDT=0000 00000000 00000000 00008200 DPL=0 LDT
TR =0028 f032c02c 00000067 00408900 DPL=0 TSS32-avl
GDT=     f0128340 00000067
IDT=     f032b260 000007ff
CR0=80050033 CR2=efff7ffc CR3=0036e000 CR4=00000000
DR0=00000000 DR1=00000000 DR2=00000000 DR3=00000000 
DR6=ffff0ff0 DR7=00000400
EFER=0000000000000000
Triple fault.  Halting for inspection via QEMU monitor.
qemu: terminating on signal 15 from pid 4777

debug发现是启动流程
cons_init();

cprintf("6828 decimal is %o octal!\n", 6828);

// Lab 2 memory management initialization functions
mem_init();

// Lab 3 user environment initialization functions
env_init();
trap_init();

// Lab 4 multiprocessor initialization functions
mp_init();
lapic_init();

// Lab 4 multitasking initialization functions
pic_init();

// Acquire the big kernel lock before waking up APs
// Your code here:
lock_kernel();
// Starting non-boot CPUs
boot_aps();

里面的lapic_init();的	lapicw(SVR, ENABLE | (IRQ_OFFSET + IRQ_SPURIOUS));出问题
debug到这行进入trap 到 page fault 到page fault handler
![1688481124377](https://github.com/Leavaway/csnotes/assets/86211987/11cb8737-1ebe-4bb4-8715-8509cd19066a)
在GDB里面运行的最后一行报错前的代码是: 0x3a0946d5: Error while running hook_stop: Cannot access memory at  address 0x3a0946d5
报错可能是由于尝试访问无效内存地址而引发的页面错误 lapic_init函数中不正确地设置了APIC的内存映射。
可能是mmio_map_region设置错误, 检查发现是boot_map_region(kern_pgdir, base, size, pa, PTE_P|PTE_PCD|PTE_PWT);应该是boot_map_region(kern_pgdir, base, size, pa, PTE_W|PTE_PCD|PTE_PWT);
原来的代码权限不足导致了错误。

在传统的Unix系统中，当一个页错误（page fault）发生时，处理过程会切换到内核态来进行处理，包括加载新的页面、处理写时复制（copy-on-write）等。内核需要维护足够的信息来确定针对每个页错误该采取何种行动
而在JOS系统中，用户环境可以设定一个页错误处理程序，当页错误发生时，它将在用户态的一个特别设定的异常堆栈上进行处理，而不是切换到内核态。这一设计理念简化了内核的复杂性，同时为用户程序提供了更大的灵活性。
同时，用户态的页错误处理程序需要利用JOS的系统调用来执行一些特权操作，如修改页面表或分配新的物理页面。这些系统调用在内核态中运行，并在完成任务后返回用户态。

当发生页错误时，JOS内核会将错误信息压入用户环境的异常栈，并调用env_pgfault_upcall指向的函数进行处理。这个函数就是用户环境注册的页错误处理函数。这样，页错误的处理就在用户态进行，而不是切换到内核态。这使得用户环境可以自定义页错误的处理逻辑，增加了系统的灵活性


在这个环境（env）运行期间，异常栈一直存在并不会被“刷新”或清空。当一个异常（如页错误）发生时，esp会向下移动（也就是说，向栈底方向“压栈”），然后在当前的esp位置创建一个新的UTrapframe结构体。这个UTrapframe包含了异常发生时的所有寄存器状态。

当异常处理完成后，通常会恢复这个UTrapframe中的寄存器状态，并将esp移动回原来的位置，以此来“弹栈”并返回到异常发生前的状态。

但是，一般来说，除非发生了另一个异常，否则异常栈中的内容不会被显式地清除或刷新。也就是说，即使一个异常处理完成并且esp已经“弹栈”，异常栈中的数据实际上还是存在的，只是不再被使用。这就是为什么栈有时被称为是有“历史”的数据结构。

在JOS这样的操作系统中，这种设计使得在一个环境中连续发生多个异常时能够正确处理。例如，如果一个页错误处理程序本身也触发了一个页错误，那么操作系统能够在异常栈上为第二个页错误创建另一个UTrapframe，并且能够正确地处理这两个异常。

![1689126247274](https://github.com/Leavaway/csnotes/assets/86211987/9836e25e-6f11-4d8f-9f89-1782c3b880dc)

导致无法通过测试, 一开始以为是调度问题因为应该是0000创建好1000之后yield调度让1000创建后面的env, 但是在init里面ENV_CREATE(user_yield, ENV_TYPE_USER);
	ENV_CREATE(user_yield, ENV_TYPE_USER);
	ENV_CREATE(user_yield, ENV_TYPE_USER);多出来三行这个导致了在运行init的时候是bsp，所以这三行是直接以bsp的0000创建了3个env
 

内核态处理：
用户程序执行一个会触发陷阱或中断的操作，例如系统调用、除以零、访问非法内存等。

处理器立即停止当前用户程序的执行，保存当前的程序计数器和处理器状态，然后设置新的程序计数器为内核中定义的中断服务例程（ISR）或陷阱处理程序的地址。

处理器提升特权级别到内核态。

中断服务例程或陷阱处理程序开始执行，此时系统已经处于内核态。

内核完成所需的操作后，会通过执行一个特殊的指令（例如iret在x86架构上）来恢复之前保存的程序计数器和处理器状态，并将特权级别降低回用户态，继续执行用户程序。

[00000000] new env 00001000
[00001000] new env 00001001
[00001001] user panic in <unknown> at lib/fork.c:30: pgfault: cant access to cow or write
遇到了权限问题, 检查fork函数和pgfault函数 应该是没问题的。检查sys_ipc_try_send发现把insert的pgdir填错了。。 应该是des, 不是curenv
if(des->env_ipc_dstva!=0){
			if(page_insert(curenv->env_pgdir,pp,des->env_ipc_dstva,perm)<0){
				return -E_NO_MEM;
			}
		}

## LAPIC
在多处理器系统中，每个处理器都有一个本地高级可编程中断控制器（Local Advanced Programmable Interrupt Controller，简称LAPIC）。LAPIC用于处理中断和中断的分发，特别是在多处理器系统中，它可以处理来自不同源的中断，并将它们分发到适当的处理器。

每个处理器的LAPIC都有一个唯一的ID，这个ID被用于标识中断的目的地。当一个中断发生时，它会被发送到具有特定ID的LAPIC，然后由该LAPIC将中断路由到相应的处理器。

此外，LAPIC还支持中断优先级，这意味着可以为中断设置优先级，以决定中断处理的顺序。高优先级的中断可以打断正在处理的低优先级中断。

在JOS中，LAPIC被用于处理和分发中断。例如，时钟中断和键盘中断都是由LAPIC处理并分发给处理器的。

