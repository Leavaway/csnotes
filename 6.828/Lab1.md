## Part 1: PC Bootstrap
  ### The PC's Physical Address Space
  ![1685329528512](https://github.com/Leavaway/csnotes/assets/86211987/7891db58-7666-4460-b1b9-f87d2b4246fc)<br/>
  16位8088处理器只有1MB的物理内存, 从0x00000000到0x000FFFFF, 而且只有开始的640KB可以作为RAM使用, 剩下的地址被用作其他的用途<br/>
  ### The ROM BIOS
  [f000:fff0] 0xffff0:	ljmp   $0xf000,$0xe05b -> 运行的第一条汇编指令<br/>
  [f000:fff0] 0xffff0 -> f000 是段选择器，后面的 fff0 是偏移地址。在实模式下，他们共同定义了一个内存地址。<br/>
  在实模式下，物理地址的计算方式是：物理地址 = 段地址（segment）* 16 + 偏移地址（offset）<br/>
  所以可以得到这个物理地址：f000 * 16 + fff0 = ffff0<br/>
  ljmp $0xf000,$0xe05b -> 长跳转（long jump）指令，这条指令将控制权转移到物理地址 0xfe05b 上<br/>
  elf文件: elf是一种文件格式，主要被用来把程序存放到磁盘上。是在程序被编译和链接后被创建出来的。一个elf文件包括多个段。对于一个可执行程序，通常包含存放代码的文本段(text section)，存放全局变量的data段，存放字符串常量的rodata段。elf文件的头部就是用来描述这个elf文件如何在存储器中存储。<br/>
