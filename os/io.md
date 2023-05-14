## I/O
  概念: 输入是指数据从外部环境（如用户、传感器、网络或其他计算机）进入计算机，而输出是指数据从计算机传输到外部环境。 按信息交换的单位可分为块设备和字节设备<br/>
  
### I/O控制器
  功能: 1) 接受和识别CPU发出的命令: 有相应的控制寄存器来存放命令和参数 <br/>
  2) 向CPU报备设备的状态: 有状态寄存器来存放I/O设备当前的状态 <br/>
  3) 数据交换: 有数据寄存器来暂存数据 <br/>
  4) 地址识别: 区分各个寄存器<br/>
  组成: <img width="600" alt="1684073056006" src="https://github.com/Leavaway/csnotes/assets/86211987/1a75fad6-714d-4f3b-9464-6cbdb07ef354"><br/>
### I/O控制方式
  1. 程序直接控制方式: CPU干预频率高 CPU和IO设备串行工作导致利用率低<br/>
  <img width="600" alt="1684078036492" src="https://github.com/Leavaway/csnotes/assets/86211987/4d31ad6b-3825-4e46-a809-c265d93234a0"><br/>
  2. 中断驱动方式: 引入了中断机制, 可以并行工作, 但是每个字在I/0设备与内存之间的传输，都需要经过CPU。而频繁的中断处理会消耗较多的CPU时间<br/>
  <img width="600" alt="1684078404522" src="https://github.com/Leavaway/csnotes/assets/86211987/59bc968a-1cbb-49c7-a128-586413620eb1"><br/>
  3. DMA(Direct memory access): 主要用于块设备的IO控制, 仅在传输一个或者多个数据块(连续的)的开始和结束时才需要CPU干预<br/>
  <img width="600" alt="1684078806335" src="https://github.com/Leavaway/csnotes/assets/86211987/4a30de80-c910-4035-b3b5-200857140c2f"><br/>
  4. 通道控制方式: 使用通道(一种硬件)识别并执行一系列通道指令, 通道程序放在内存中, CPU指明通道程序位置和操作设备等信息就不再干预, 可以一次读写一组数据块, 且并行度高<br/>
  


