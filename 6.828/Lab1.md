## Part 1: PC Bootstrap
  ### The PC's Physical Address Space
  ![1685329528512](https://github.com/Leavaway/csnotes/assets/86211987/7891db58-7666-4460-b1b9-f87d2b4246fc)<br/>
  16位8088处理器只有1MB的物理内存, 从0x00000000到0x000FFFFF, 而且只有开始的640KB可以作为RAM使用, 剩下的地址被用作其他的用途<br/>
  ### The ROM BIOS
  [f000:fff0] 0xffff0:	ljmp   $0xf000,$0xe05b -> 运行的第一条汇编指令<br/>
  [f000:fff0] 0xffff0 -> f000 是段选择器，后面的 fff0 是偏移地址。在实模式下，他们共同定义了一个内存地址。<br/>
  在实模式下，物理地址的计算方式是：物理地址 = 段地址（segment）* 16 + 偏移地址（offset）<br/>
  所以可以得到这个物理地址：f000 * 16 + fff0 = ffff0<br/>
  内存映射I/O (MMIO)：在这种方式中，硬件设备的寄存器被映射到系统的物理内存地址空间中。CPU使用标准的内存访问指令（例如load和store）来访问这些地址，从而与硬件设备通信<br/>
  端口映射I/O (PMIO)：在这种方式中，硬件设备的寄存器被映射到一个独立的I/O地址空间。这个地址空间是与内存地址空间分开的，并且CPU使用特殊的I/O指令（在x86上，这些是in和out  指令）来访问这个空间<br/>
  ljmp $0xf000,$0xe05b -> 长跳转（long jump）指令，这条指令将控制权转移到物理地址 0xfe05b 上<br/>
  elf文件: elf是一种文件格式，主要被用来把程序存放到磁盘上。是在程序被编译和链接后被创建出来的。一个elf文件包括多个段。对于一个可执行程序，通常包含存放代码的文本段(text section)，存放全局变量的data段，存放字符串常量的rodata段。elf文件的头部就是用来描述这个elf文件如何在存储器中存储。<br/>
  elf不同段:<br/>
  VMA(链接地址)，LMA(加载地址)。其中加载地址代表的就是这个段被加载到内存中后，它所在的物理地址。链接地址则指的是这个段希望被存放到的逻辑地址<br/>
   Idx Name          Size      VMA       LMA       File off  Algn<br/>
  0 .text         0000178e  f0100000  00100000  00001000  2**2<br/>
                  CONTENTS, ALLOC, LOAD, READONLY, CODE<br/>
  text段存放程序的可执行指令<br/>
  1 .rodata       0000072b  f01017a0  001017a0  000027a0  2**5<br/>
                  CONTENTS, ALLOC, LOAD, READONLY, DATA<br/>
  rodata段存放只读数据, 比如C编译器产生的ASCII string constants<br/>
  2 .stab         00004249  f0101ecc  00101ecc  00002ecc  2**2<br/>
                  CONTENTS, ALLOC, LOAD, READONLY, DATA<br/>
  3 .stabstr      00008aff  f0106115  00106115  00007115  2**0<br/>
                  CONTENTS, ALLOC, LOAD, READONLY, DATA<br/>
  4 .data         0000a300  f010f000  0010f000  00010000  2**12<br/>
                  CONTENTS, ALLOC, LOAD, DATA<br/>
  data段存放程序的初始化数据, such as global variables declared with initializers like int x = 5<br/>
  5 .bss          00000648  f0119300  00119300  0001a300  2**5<br/>
                  CONTENTS, ALLOC, LOAD, DATA<br/>
  bss段是链接器给未初始化全局变量比如int x预留的空间<br/>
  6 .comment      00000011  00000000  00000000  0001a948  2**0<br/>
                  CONTENTS, READONLY<br/>
  ### C pointer exercise
    int a[4];
    int *b = malloc(16);
    int *c;
    int i;

    printf("1: a = %p, b = %p, c = %p\n", a, b, c);

    c = a;
    for (i = 0; i < 4; i++)
	a[i] = 100 + i;
    c[0] = 200;
    printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c[1] = 300;
    *(c + 2) = 301;
    3[c] = 302;
    printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = c + 1;
    *c = 400;
    printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = (int *) ((char *) c + 1);
    *c = 500;
    printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    b = (int *) a + 1;
    c = (int *) ((char *) a + 1);
    printf("6: a = %p, b = %p, c = %p\n", a, b, c);
   结果:<br/>
   
    1: a = 0x7ffdffcc1e50, b = 0x559b216ec260, c = 0x1
    a输出的是数组a的首地址; b输出的是指针b所指向的操作系统分配给它的空间的起始地址; 未初始化的变量c的地址是0x1
    2: a[0] = 200, a[1] = 101, a[2] = 102, a[3] = 103
    3: a[0] = 200, a[1] = 300, a[2] = 301, a[3] = 302
    4: a[0] = 200, a[1] = 400, a[2] = 301, a[3] = 302
    5: a[0] = 200, a[1] = 128144, a[2] = 256, a[3] = 302
    c = (int *) ((char *) c + 1);这行代码的目的是先把c转换成一个char类型指针, 一个指针+1 会移动这个指针的size的距离, int类型指针size一般是4
    所以+1对于int类型指针会移动4个字节的距离, 而char类型指针的size是1, 只会移动一个字节
    6: a = 0x7ffdffcc1e50, b = 0x7ffdffcc1e54, c = 0x7ffdffcc1e51
  ### print 
   print通过kern/printf.c, lib/printfmt.c, and kern/console.c实现, 其中console.c中的cputchar是被console.c提供给给另外2个的调用接口.
   console.c:
     `High'-level console I/O.  Used by readline and cprintf.
	void
	cputchar(int c)
	{
	    cons_putc(c);
	}

	// output a character to the console
	static void
	cons_putc(int c)
	{
	    serial_putc(c);
	    lpt_putc(c);
	    cga_putc(c);
	}
   其中serial_putc(c): 
   	#define COM1        0x3F8
	#define COM_TX        0    // Out: Transmit buffer (DLAB=0)
	#define COM_LSR        5    // In:    Line Status Register
	#define COM_LSR_TXRDY    0x20    //   Transmit buffer avail

	static void
	serial_putc(int c)
	{
	    int i;

	    for (i = 0;
		 !(inb(COM1 + COM_LSR) & COM_LSR_TXRDY) && i < 12800;
		 i++)
		delay();

	    outb(COM1 + COM_TX, c);
	}
   这个函数主要通过一个for loop检查和等待缓存区清空
   在for loop中, COM1 + COM_LSR指示了0x3F8+5为0x3FD这个地址, 查询文档可知这个地址为line status register, COM_LSR_TXRDY为00100000, 通过
   按位与这个inb(COM1 + COM_LSR) & COM_LSR_TXRDY)可以从0x3FD这个IO端口地址读一字节并且将其与COM_LSR_TXRDY进行按位与比较, 即检查第六位是否为0,
   即第六位指示Transmitter Holding Register Empty, 如果为1则指示为空。这个方法可用于检查寄存器中的特定位，以确定硬件的某个状态。
   
   lpt_putc 函数通过并口发送一个字节
   
   cga_putc 函数，用于在 CGA (Color Graphics Adapter) 显示屏上输出字符。先判断有没有高24位的设置， 如果没有就设置为0x0700。 然后取低8位进入switch判断和处理
   特殊情况。 随后处理当光标位置超出屏幕范围时的情况，最后移动光标

   
    
   
