### GPIO 通用输入输出
GPIO 是 General Purpose Input/Output（通用输入/输出）的缩写，是一种通用的、没有特定功能的数字信号引脚，其功能由软件定义。每个 GPIO 都可以被配置为输入或输出。

在嵌入式系统中，GPIO 是最常见的方式来与其他数字系统或数字器件进行交互。你可以将 GPIO 引脚用于读取数字信号（输入模式）或输出数字信号（输出模式）。

在输入模式下，GPIO 引脚可以用来读取来自外部设备的数字信号，比如按钮的状态。

在输出模式下，GPIO 引脚可以控制外部设备，比如 LED。

在 STM32 微控制器中，每个 GPIO 引脚可以配置为多种模式，包括输入、输出、模拟、中断以及一些特定功能模式（如 I2C，SPI，USART 等）。除此之外，STM32 的 GPIO 引脚还支持中断，这使得在某些特定事件发生时，例如引脚电平改变时，可以立即触发一个处理程序。

在编程时，通常使用 GPIO 库或直接操作硬件寄存器来控制 GPIO 引脚。例如，你可以设置引脚模式（输入、输出等），设置引脚电平（高或低），以及读取引脚状态。

GPIO位结构


上拉模式和下拉模式: 在引脚没有输入时候可以设置默认的电平

施密特触发器: 信号整形，设置2个阈值来进行信号判断，只有高于高阈值或者低于低阈值才会引起信号变化，有效避免因为信号波动导致的输出抖动现象

更改输出寄存器的某一位: 1) 读出更改后写回 2)使用位设置/清楚寄存器 3)位带


为什么需要这么多时钟？
一是在一个故障的时候, 别的可以应急。而是多个时钟源可以让外设选择相应频率的外设源
### EXTI 外部中断
stm中断

![1690179692496](https://github.com/Leavaway/csnotes/assets/86211987/bec4e9c2-58be-4131-bdb1-de2cfefdb918)


软中断和硬中断的区别

软中断和硬中断是两种不同类型的中断。软中断是由程序调用发生的，而硬中断是由外设引发的1。硬中断发生的时间是随机的，而软中断发生的时间是由程序控制的1。硬件中断处理程序要确保它能快速地完成它的任务，这样程序执行时才不会等待较长时间

NVIC统一管理 抢占优先级和响应优先级: 抢断优先级高的可以中断嵌套, 响应优先级高的可以优先排队, 这两个值均相同的按照中断号排队

低速外设和高速外设的区别是，APB1上面挂载的是低速外设，APB2上挂载高速外设。APB2可以工作在72MHz下，而APB1最大是36MHz。

EXTI为extern interrupt 外部中断，监测指定GPIO口的电平信号，监测的GPIO电平变化时向NVIC发出中断信号，排到后中断CPU并且执行相应的中断程序，
支持上升沿/下降沿/双边沿/软件触发  响应: 中断响应/事件响应
EXTI有16个GPIO PIN通道和4个额外的通道, 所以同一个PIN值不能同时中断

STM32微控制器中的GPIO（General Purpose Input/Output）端口有一个很重要的特性，那就是它们可以被重新映射到其他功能，这就是所谓的“Alternate Function”。这些Alternate Function可以是各种外设的接口，如USART、I2C、SPI、TIM等。
AFIO（Alternate Function I/O）是STM32中用于管理这种功能映射的硬件部件。通过配置AFIO，我们可以选择将GPIO端口的某些引脚用作特定外设的接口，或者恢复它们为普通的GPIO。
例如，如果我们想使用USART1，但是又不想使用它默认的引脚（PA9和PA10），那么可以通过配置AFIO，将USART1的TX和RX线映射到其他的GPIO引脚上。
AFIO 引脚复用功能选择和重定义(数据选择器),  引脚复用功能引脚重映射, 中断引脚选择。
EXTI框图: 
![1690181122540](https://github.com/Leavaway/csnotes/assets/86211987/65a4bdd3-60fe-4a09-903a-c055a427ca36)

配置外部中断步骤: 1.配置GCC, 2. 配置GPIO 3. 配置AFIO 4. 配置EXTI 5. 配置NVIC
STM32时钟详解: https://zhuanlan.zhihu.com/p/345114910

### TIM 定时中断
TIM定时器和时钟比如HSI、HSE等的联系是，TIM定时器需要时钟源来驱动，而HSI、HSE等是STM32的时钟源之一，它们可以作为TIM定时器的时钟源。HSI是高速内部时钟、RC振荡器，频率为8MHz；HSE是高速外部时钟，即晶振，可接石英/陶瓷谐振器或接外部时钟源，频率范围为4MHz~16MHz。TIM2~TIM7挂载在APB1分频器上，TIM1和TIM8挂载在APB2分频器上；APB1上面挂载的是低速外设，APB2上挂载高速外设。

![1690360586221](https://github.com/Leavaway/csnotes/assets/86211987/4dea7565-96df-4799-a042-c047b89ee56a)

定时中断基本结构:
![1690361512626](https://github.com/Leavaway/csnotes/assets/86211987/ce4b242c-4986-44bc-a2bd-aeb5bd8c0d75)

定时频率计算: ![1690454254073](https://github.com/Leavaway/csnotes/assets/86211987/da137406-061d-427c-8e27-4b8fb7224f2d)

### TIM输出比较

PWM:脉冲宽度调制
需要在具有惯性的系统中使用 
输出比较模式:
![1690764157680](https://github.com/Leavaway/csnotes/assets/86211987/b442f3b4-2b54-4241-bc5f-519127ed994d)
PWM基本结构: 
![1690764678178](https://github.com/Leavaway/csnotes/assets/86211987/2262ed46-5f09-45e5-8ecf-72bb3b150fc7)

### TIM输入捕获

![1690800079983](https://github.com/Leavaway/csnotes/assets/86211987/9db443ee-4430-4d07-8d5b-e35eb8c761ca)

![1690800953070](https://github.com/Leavaway/csnotes/assets/86211987/a5432485-de22-43b4-9249-82feead4af26)

![1690802999500](https://github.com/Leavaway/csnotes/assets/86211987/1e875f7c-dfcd-4f0a-93aa-6f9a6290af59)

### 定时器的编码器接口

![1690814711117](https://github.com/Leavaway/csnotes/assets/86211987/3e84d8c0-7545-4317-b162-165adce9f635)

![1690815669925](https://github.com/Leavaway/csnotes/assets/86211987/c762d2ae-70d9-44d3-872e-e1797db89b36)

### ADC数模转换器
![1690866912166](https://github.com/Leavaway/csnotes/assets/86211987/032c0e1c-cb83-406a-a5c0-50f109544962)

![1690868247713](https://github.com/Leavaway/csnotes/assets/86211987/0848659b-fbfb-45bf-8668-912763db99ef)

STM32 ADC:
![1691034157754](https://github.com/Leavaway/csnotes/assets/86211987/64971d9c-b1d4-4295-8532-39c143ce685f)


转换模式: 单次转换，非扫描模式。只有序列1的通道会被转换，结束后置EOC标志位为1随后停止
连续转换，非扫描模式。相比于单次转换，结束后会立刻开始下一轮的转换
单次转换，扫描模式。通道里的指定数目内的都会被转换，结束后置EOC标志位为1随后停止
连续转换，扫描模式。相比于单次转换，结束后会立刻开始下一轮的转换

AD转化的步骤: 采样 保持 量化 编码
总转换时间为: 采样时间+12.5ADC周期  如ADCCLK为14MHz, 采样时间为1.5个ADC周期 量化编码需要12.5，则总共为14ADC周期 总时间为1us

### DMA

![1690962500007](https://github.com/Leavaway/csnotes/assets/86211987/a77dc253-2cd2-4ec6-98c0-19ff27bc6bb1)
通常外设到存储器用硬件触发，存储器到存储器用软件触发
STM32DMA:</br>
![1691034353931](https://github.com/Leavaway/csnotes/assets/86211987/cb1aaf0f-baf6-4e63-bd46-75fec68b178d)

![1691034260187](https://github.com/Leavaway/csnotes/assets/86211987/a3e908d7-30da-44a1-88c2-862130615d03)

![1690962882441](https://github.com/Leavaway/csnotes/assets/86211987/164647ff-9bd7-4750-b0c2-e15e174592bd)

### USART
串口：

![1691044243896](https://github.com/Leavaway/csnotes/assets/86211987/b09e6525-076e-491f-8619-0d2a21afef87)

![1691052631558](https://github.com/Leavaway/csnotes/assets/86211987/05254854-e06a-4a3c-9acd-930dd2c790d7)

STM32起始位检测和噪声处理

![1691053732369](https://github.com/Leavaway/csnotes/assets/86211987/30ea7d01-1d9a-4af9-b492-121a5af31a43)

在收到下降沿(起始位)信号后以16倍波特率进行16次采样。如果3个采样点都为’0’(在第3、5、7位的第一次采样，和在第8、9、10的第二次采样都为’0’)，
则确认收到起始位，这时设置RXNE标志位，如果RXNEIE=1，则产生中断。 确定收到起始位后使用8,9,10进行采样

收到起始位 后的数据采样 (也在8.9.10连续进行3次采样) 也按2:1确实噪声, 如果不是全为1或者0则置噪声标志位NE。

### I2C

![1691286386115](https://github.com/Leavaway/csnotes/assets/86211987/f75d34f6-9664-43c7-bd8c-6da2dc93fafc)

![image](https://github.com/Leavaway/csnotes/assets/86211987/0c050993-ad60-46c5-b0a3-18c2c94cb560)

起始条件: 在SCL高电平的时候, SDA从高电平切换到低电平

终止条件:  在SCL高电平的时候, SDA从低电平切换到高电平

发送一个字节:SCL低电平期间，主机将数据位依次放到SDA线上(高位先行)，然后释放SCL，从机将在SCL高电平期间读取数据位所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次即可发送一个字节

接收一个字节i:SCL低电平期间，从机将数据位依次放到SDA线上(高位先行)，然后释放SCL，主机将在SCL高电平期间读取数据位所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次即可接收一个字节(主机在接收之前，需要释放SDA)0

I2C时序: 指定地址写: 对于指定设备的指定地址,写入指定数据 

当前地址读:对于指定设备(Slave Address)，在当前地址指针指示的地址下读取从机数据(Data)

指定地址读:对于指定设备在指定地址 (Reg Address)下(Slave Address)，读取从机数据(Data)

I2C硬件: 

![1691460632663](https://github.com/Leavaway/csnotes/assets/86211987/98891d41-3c0f-40a7-a28c-e80d5fced821)

![1691461847295](https://github.com/Leavaway/csnotes/assets/86211987/47f9056a-a084-4f28-b6d8-3899d8b8db72)

![1691462077726](https://github.com/Leavaway/csnotes/assets/86211987/5112d0f7-0910-4e66-9309-a7b0a63f4637)

### SPI
移位示意图:

![1691551240537](https://github.com/Leavaway/csnotes/assets/86211987/b8af159c-4da0-4181-8af1-38fceb1922ef)

起始和终止条件: 设置SS高低电平

模式1 : SCK上升沿置电平，下降沿读取电平

Flash操作注意事项: 

![1691564076403](https://github.com/Leavaway/csnotes/assets/86211987/e9378c8b-2d22-4c18-9283-c83023f70dfe)

![1691650699892](https://github.com/Leavaway/csnotes/assets/86211987/2085f317-bd1b-4414-9c5e-a824f25282a3)

SPI硬件框图: 

![1691655635189](https://github.com/Leavaway/csnotes/assets/86211987/83cf8c04-184a-47c5-8754-93cfc0736628)

![1691656994913](https://github.com/Leavaway/csnotes/assets/86211987/c29441e1-ef0d-40ec-8ded-8df1f6a49b39)



![1691674930262](https://github.com/Leavaway/csnotes/assets/86211987/2f35db21-c8e6-48ce-aa68-13f30edbac25)

![1691689190160](https://github.com/Leavaway/csnotes/assets/86211987/d74b3d4f-5598-42ac-ad18-a2cf619276d4)

### Unix, BKP, RTC

![1691723754584](https://github.com/Leavaway/csnotes/assets/86211987/8404fed6-6ef0-485d-92df-dac3da837fe6)

BKP简介: 

![1691739138121](https://github.com/Leavaway/csnotes/assets/86211987/c542db67-ed89-4b84-a304-230dfa1e9164)

![1691744267005](https://github.com/Leavaway/csnotes/assets/86211987/98e3d3ff-33d9-4e8f-b840-4a0f63566983)

图中灰色部分为断电或者待机时仍然供电区域

### PWR

![1691815854033](https://github.com/Leavaway/csnotes/assets/86211987/0715c567-054a-4d67-802d-daaa4a508054)

![1691816291555](https://github.com/Leavaway/csnotes/assets/86211987/b74afeb7-0342-4f9f-bd20-f9909042f3b7)

![1691821853000](https://github.com/Leavaway/csnotes/assets/86211987/2372a29c-7380-4880-b055-73188ded2bf3)

### PID
PID公式: 

![1692459457515](https://github.com/Leavaway/csnotes/assets/86211987/4489bf80-0466-4b99-816e-778c723a6f21)

P 比例: 设置kp I 设置偏差积分ki D: 设置偏差微分kd
![1692460806320](https://github.com/Leavaway/csnotes/assets/86211987/f9613cfa-d42c-4522-8df1-cea2662ac25e)

积分限幅：防止特殊情况下I积分过大，所以设置限幅

积分分离: 在程序启动，或大幅度增减目标值时，短时间内会造成系统有特别大的偏差，会造成PID运算的积分积累，致使输出量特别大，很容易导致超调，甚至会引起系统较大的震荡。 因此在积分较大时取消积分作用

微分先行: 把传感器值接到D。让target先给IP，消除了target突变的影响
