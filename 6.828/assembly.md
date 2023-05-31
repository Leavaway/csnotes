# 汇编指令
  ## 指令后缀
  "b"，表示 "byte"，表示操作的对象是 8 位的<br/>
  "w"，表示 "word"，表示操作的对象是 16 位的<br/>
  "l"，表示 "long"，表示操作的对象是 32 位的<br/>
  "q"，表示 "quadword"，表示操作的对象是 64 位的<br/>
  ## 跳转指令
   jne target 全称是 Jump if Not Equal。它会检查前面的比较指令（例如 cmpl）设置的条件标志位，如果条件标志表示"不等"（即比较的两个操作数不相等），那么就跳转到指定的地址执行代码<br/>
   jmp target 直接跳转 <br/>
  ## 比较指令
   cmpl S1,S2 比较两个操作数，并根据比较的结果设置条件标志寄存器（EFLAGS）<br/>
   test 执行位测试操作, 接受两个操作数，执行一个按位与（AND）操作，但是不保存结果，只改变标志位寄存器<br/>
  ## 算数和逻辑指令
   add operand1, operand2 将 operand1 和 operand2 进行加法操作，并将结果存储在 operand2 中<br/>
   sal 指令执行算术左移操作，也就是将指定的位数向左移动，并在右边填充 0<br/>
   xor operand1, operand2 将 operand1 和 operand2 进行异或操作，并将结果存储在 operand2 中<br/>
   imul 整数乘法<br/>
  ## 处理器操作指令
   cli Clear Interrupt, 用于清除Interrupt Enable Flag 当这个标志被清除时，处理器将不再响应可屏蔽的硬件中断，直到这个标志再次被设置。这个指令常常在需要进行一些不能被中断的重要操作时使用<br/>
   cld Clear Direction Flag, 清除方向标志（Direction Flag）方向标志用于控制字符串操作指令（如 MOVSB、MOVSD、STOSB、STOSD 等）的处理方向。当方向标志被清除时，字符串操作指令将从低地址向高地址处理数据；当方向标志被设置时，字符串操作指令将从高地址向低地址处理数据<br/>
  ## 端口操作指令
   in src dest I/O端口输入<br/>
   out src dest I/O端口输出<br/>
  ## 目的地址传送指令
   lea src dest 装入有效地址, 将src的地址的值计算出来然后装入到dest, 常常被用作一个快速的算术运算指令, 比如 leaq (%rdi,%rsi), %rax <br/>
  ## 其他
   lgdt/lidt 加载全局/中断描述符表寄存器<br/>
   cmovcc 条件移动<br/>
   <br/>
# 寄存器
 
