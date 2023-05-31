从C源文件到可执行文件:<br/>
![1685491550182](https://github.com/Leavaway/csnotes/assets/86211987/3f95c6db-8d72-454b-9b45-896f59d2384c)<br/>
![1685493474844](https://github.com/Leavaway/csnotes/assets/86211987/86878abf-e32b-47af-afe6-0e794cb6c373)<br/>
## EFLAGS 寄存器: 包含了一系列的标志位，这些标志位提供了有关处理器的状态信息，比如最近的算术或逻辑操作的结果的属性<br/>
常用标志位<br/>
零标志（Zero Flag，ZF）：如果最近的操作的结果为零，则此标志被设置。<br/>
符号标志（Sign Flag，SF）：如果最近的操作的结果为负，则此标志被设置。<br/>
进位标志（Carry Flag，CF）：如果最近的操作导致了进位或借位，则此标志被设置。<br/>
溢出标志（Overflow Flag，OF）：如果最近的操作导致了有符号溢出，则此标志被设置。<br/>
奇偶标志（Parity Flag，PF）：如果最近的操作的结果的最低有效字节中的位有偶数个 1，此标志被设置。<br/>
## x86-64寄存器:
![1685501007577](https://github.com/Leavaway/csnotes/assets/86211987/54859f23-2739-4fa4-96fe-9b620b0a5527)<br/>
## Conditional Move
cmovcc Conditional Move 指令可以提高程序的性能，因为它可以避免程序中的条件跳转。在现代处理器中，跳转预测（Branch Prediction）是一个重要的性能优化技术，如果预测错误，处理器需要清空指令管道并重新加载指令，这会导致显著的性能损失。通过使用 Conditional Move 指令，可以减少这种情况的发生<br/>
## 循环
![1685501408380](https://github.com/Leavaway/csnotes/assets/86211987/45726556-437b-4a53-b1c9-e6d6bf04f8bf)<br/>
## switch
![1685501491200](https://github.com/Leavaway/csnotes/assets/86211987/459a8ff3-b876-47bb-aa1a-3ca80f5cf585)<br/>
汇编中可以使用跳转表（Jump Table）的方式来实现类似switch的功能。跳转表是一种非常有效的方式来实现多路分支的情况。<br/>
