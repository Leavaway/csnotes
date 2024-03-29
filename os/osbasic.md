# 操作系统
  ## 基本概念
  目标: 向上层提供方便易用的服务<br/>
  定义: 控制和管理计算机系统的软件和硬件资源，并合理地组织调度工作和资源来给用户提供接口和环境，是最基本的系统软件<br/>
  功能: 文件管理，内存管理，CPU管理，设备管理<br/>
  特征: 并发，共享，虚拟，异步<br/>
  发展和阶段：<br/>
    1. 手工操作阶段<br/>
    2. 批处理阶段(单道批处理系统, 多道批处理系统)<br/>
    3. 分时操作系统<br/>
    4. 实时操作系统(硬实时系统, 软实时系统)<br/>
    5. 网络操作系统<br/>
    6. 分布式操作系统<br/>
    7. 个人计算机操作系统<br/>
  ## 运行机制
   两类程序: 内核程序, 应用程序<br/>
   两类指令: 特权指令, 非特权指令<br/>
   两种处理器状态: 内核态, 用户态<br/>
   内核: 内核(Kernel)是操作系统最重要最核心的部分, 油很多内核程序组成<br/>
   内核态->用户态: 一条修改PSW的特权指令<br/>
   用户态->内核态: 由中断引起，硬件自动完成<br/>
  ## 中断和异常
   内中断(异常): 陷入(由应用程序使用陷入指令故意引发),故障(由错误条件入缺页故障引起, 可能被内核程序修复), 终止(由致命错误引起且内核程序无法修复如整数除零)<br/>
   外中断: 时钟中断, I/O中断请求<br/>
  ## 系统调用
   过程: 传递系统调用参数->执行陷入指令(用户态)->处理系统调用的内核程序(核心态)->返回<br/>
    
## 寄存器
   ### IA32
   IA32有8个32位的通用寄存器，这8个通用寄存器都是由8086相应16位通用寄存器扩展成32位而得：<br/>
   EAX：一般用作累加器<br/>
   EBX：一般用作基址寄存器（Base）<br/>
   ECX：一般用来计数（Count）<br/>
   EDX：一般用来存放数据（Data）<br/>
   ESP：一般用作堆栈指针（Stack Pointer）<br/>
   EBP：一般用作基址指针（Base Pointer）<br/>
   ESI：一般用作源变址（Source Index）<br/>
   EDI：一般用作目标变址（Destinatin Index）<br/>
   ![1685604554073](https://github.com/Leavaway/csnotes/assets/86211987/c393aae0-853d-4056-81ca-7d1d929f3bcd)<br/>
   当这些寄存器用在函数调用时候经常会被用来临时存储变量, 但是caller和callee需要注意保存好寄存器里面原来存储的值<br/>
   ### x86-64
   x86_64架构有16个通用寄存器，相比IA32多了8个（r8 至 r15时x86_64新增的）<br/>
   ![image](https://github.com/Leavaway/csnotes/assets/86211987/be0b87b6-995c-46f3-a732-b04089436503)<br/>
   和IA32主要区别是：<br/>
   1）6个寄存器用来保存参数，多出的参数类似x86入栈；<br/>
   2）若存在闲置的寄存器的话，局部变量可以直接缓存到闲置寄存器中，过多局部变量类似x86入栈；<br/>
   3）因为是64位，rsp栈指针每次移动8个字节：类似 movq -8(%rsp),%rsp<br/>
   4）函数可以访问％rsp之后最多128个字节的内存：“红色区域”，意味着可以在通过%rsp的来在“红色区域”内存储一些临时数据。而不必使用使用多条指令。参考栈帧章节。<br/>
   5）在编译优化时，栈帧指针rbp被弃用，成为通用一般寄存器。所有对当前栈帧中的内存字段的访问引用,由%rsp进行相对寻址来实现。参考栈帧章节。<br/>
   在32bit时代，参数传递是通过入栈实现的，相对CPU来说，存储器访问太慢；这样函数调用的效率就不高。在x86-64时代，寄存器数量多了，CPU就可以利用多达6个寄存器来存储参数，多于6个的参数，依然还是通过入栈实现传递。<br/>
   因此在x86_64位机器上编程时，需要注意：<br/>
   1）为了效率尽量使用少于6个参数的函数<br/>
   2）传递比较大的参数，尽量使用指针，因为寄存器只有64位<br/>
   
   流程: <br/>
   当一个函数被调用时，使用call指令，有几件事情会自动发生：<br/>
  call 指令将当前的 EIP（执行 call 指令的下一条指令的地址）压入栈。<br/>
  EIP 设置为被调用的函数的地址，从而开始执行该函数。<br/>
  同时函数内部有prologue: <br/>
  使用 push ebp 指令将旧的 EBP（基指针）压入栈。<br/>
  设置 EBP 等于当前的栈顶，通过 mov ebp, esp。<br/>
  为局部变量分配空间，通过减少 ESP。<br/>
  
  在函数准备返回时执行epilogue操作:<br/>
  设置 ESP 等于 EBP，这样栈就回到了调用函数时的状态。<br/>
  使用 pop ebp 指令恢复旧的 EBP。<br/>
  执行 ret 指令。ret 指令会从栈中弹出一个地址（这是最初由 call 指令压入的地址）并将 EIP 设置为该地址。<br/>
   入栈: 1. 使用 push 来向栈中放入一个数据项，然后自动更新（减小）栈指针的常用指令 2. 使用 mov 指令可以一次性为多个变量预留栈空间，然后直接写入值，这在某些情况下可能比逐个 push 操作更有效率。而且，手动管理栈空间可以给编译器更多的控制和优化的可能性。<br/>
   
   寄存器部分引用自https://zhuanlan.zhihu.com/p/288636064<br/>
   
   ![image](https://github.com/Leavaway/csnotes/assets/86211987/fa121299-0f94-4d11-8112-9d80356cdc83)
