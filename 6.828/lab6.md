![1690084159094](https://github.com/Leavaway/csnotes/assets/86211987/5157f04b-e5a7-4ecc-8f0f-f817e76b87a8)![image](https://github.com/Leavaway/csnotes/assets/86211987/d9d6599d-995c-447f-a03c-e01d12293448)


## JOS 4个网络进程
The Core Network Server Environment
核心网络服务器进程由the socket call dispatcher和lwIP组成,socket call dispatcher的工作方式类似于文件服务器,用户进程使用stubs来向核心网络进程发送消息,阅读lib/nsipc.c,你会发现我们查找核心网络服务器的方式和我们查找文件服务器的方式是相同的,i386_init中以NS_TYPE_NS创建了NS进程,对每个用户进程IPC,网络服务器上的调度程序会代表用户调用合适的lwIP提供的BSD socket接口函数.
普通用户进程不能直接使用nsipc_ *类函数,相反,它们使用lib/sockets.c中的函数,这些函数提供了一个基于文件描述符的sockets API,因此用户进程通过文件描述符引用sockets,正如使用文件描述符引用硬盘中的文件一样,有些操作是socket特有的,如connect，accept等等,有些是通用的如read,write,close等等,类似于文件服务器为每个打开文件维护一个内部唯一的id一样,lwIP同样会为打开的套接字维护一个唯一的id,在文件服务器和网络服务器中，我们使用存储在struct Fd中的信息将每个进程的文件描述符映射到这些惟一的ID空间。

文件服务器和网络服务器的IPC调度程序的行为相同，但还是有一个关键区别。BSD sockets calls 比如 accept和recv 可以无限期地阻塞。如果dispatcher(调度器)让lwIP执行这些阻塞调用中的一个，调度器也会阻塞，对于整个系统，一次只能有一个未完成的网络调用。对于每个传入的IPC消息，dispatcher创建一个线程，并在新创建的线程中处理请求。如果线程阻塞，则只有该线程处于休眠状态，而其他线程继续运行。
除了核心网络进程之外，还有三个辅助进程。除了接受来自用户应用程序的消息外，核心网络进程的调度器还接受来自input和timer进程的消息。

The Output Environment
当服务于用户进程sockets calls时，lwIP将生成输出包供网卡传输。LwIP将使用NSREQ_OUTPUT IPC消息将每个要传输的包发送到输出辅助进程，这个输出包会装入到IPC消息的页面参数中。输出辅助进程负责接收这些IPC消息，并通过您即将创建的系统调用接口将包转发到设备驱动程序。

The Input Environment
网卡接收到的数据包需要注入到lwIP中。对于设备驱动程序接收到的每个包，输入进程将包从内核空间中取出(使用您将实现的内核系统调用)，并使用NSREQ_INPUT IPC消息将包发送到核心网络进程。 将输入包的功能与核心网络进程分离是因为JOS使得同时接受IPC消息和轮询或等待来自设备驱动程序的包变得困难。JOS中没有select系统调用，该调用允许环境监视多个输入源，以确定哪些输入已准备好被处理。
查看net/input.c和net/output.c，你会发现这两者都需要实现。该实现主要依赖你的系统调用接口。在实现驱动程序和系统调用接口之后，你将为这两个辅助进程编写代码。

The Timer Environment
timer进程定期向核心网络服务器发送NSREQ_TIMER IPC消息，通知它一个计时器已经过期。lwIP使用来自这个线程的计时器消息来实现各种网络超时。

### Ethernet Addressing
![1689408096208](https://github.com/Leavaway/csnotes/assets/86211987/326d4b61-3e36-4089-94f5-a4611c2a952e)

# PartA
In the general case, packet reception consists of recognizing the presence of a packet on the wire,
performing address filtering, storing the packet in the receive data FIFO, transferring the data to a
receive buffer in host memory, and updating the state of a receive descriptor.

## Receive and Transmit Description
### Packet Address Filtering:
1. Exact Unicast/Multicast
2. Promisuous Unicast
3. Multicast
4. Promisuous Multicast
5. VLAN

### Receive Descriptor Format
Receive Descriptor (RDESC) Layout: 
![1689412480700](https://github.com/Leavaway/csnotes/assets/86211987/84255d5c-9251-44fa-a357-ed0cfe8d175a)
Receive Descriptor Status Field: 
PIF, IPCS, TCPCS, VP, RSV, IXSM, EOP, DD
Receive Errors (RDESC.ERRORS) Layout:
RXE, IPE, TCPE, CXE, RSV, SEQ, SE, CE
Receive Descriptor Special Field:
VLAN, CFI, PRI

描述接受符缓冲策略: 
当内部缓冲区为空时，一旦有描述符可用（由软件写入尾指针），就会立即进行获取。

当内部缓冲区接近空时（由RXDCTL.PTHRESH决定），只要在主机内存中有足够的有效描述符（由RXDCTL.HTHRESH决定）并且没有其他更高优先级的PCI活动（如描述符获取和回写或数据包传输），就会进行预取。

当主机内存中的描述符数量大于可用的内部描述符存储时，设备可能会选择执行一个非缓存行大小的获取。如果这样做可以使下一个描述符获取对齐到缓存行边界，硬件就会执行这种非对齐的获取。在获取落后于软件的情况下，这种机制提供了最高的效率。

网络通信流程: 
当数据包从网络传输到计算机的网络接口卡（NIC）时，NIC的物理层硬件会把电信号转换为二进制数据。

NIC的硬件或固件将这些数据组装成一个网络数据包，并生成一个对应的接收描述符。

NIC通过中断通知CPU有新的数据包到达。

CPU通过DMA（Direct Memory Access）机制将数据包和描述符从NIC的内存移动到主机内存。

网络驱动程序通过读取接收描述符，获取数据包的信息，然后处理数据包，如解析网络协议，将数据传递给上层的网络协议栈。

网络协议栈处理数据包，并最终将数据传递给应用程序。

### lab6 notes
int
pci_e1000_attach(struct pci_func * pcif) 
{
    volatile uint32_t* E1000;
    pci_func_enable(pcif);
    e1000 = mmio_map_region(pcif->reg_base[0],pcif->reg_size[0]); 
    return 0;
}
 If you do use a pointer to the device register mapping, be sure to declare it volatile; otherwise, the compiler is allowed to cache values and reorder accesses to this memory.

 这些指向数组的指针和描述符中packet buffer的地址都必须是物理地址，因为硬件直接和物理RAM发生DMA，并不经过MMU。

发送初始化: 
Software should insure this memory is aligned on a paragraph (16-byte) boundary. Program the Transmit Descriptor Base Address
(TDBAL/TDBAH) register(s) with the address of the region. TDBAL is used for 32-bit addresses
and both TDBAL and TDBAH are used for 64-bit addresses.

`/* Transmit Descriptor */
struct e1000_tx_desc {
    uint64_t buffer_addr;       /* Address of the descriptor's data buffer */
    union {
        uint32_t data;
        struct {
            uint16_t length;    /* Data buffer length */
            uint8_t cso;        /* Checksum offset */
            uint8_t cmd;        /* Descriptor control */
        } flags;
    } lower;
    union {
        uint32_t data;
        struct {
            uint8_t status;     /* Descriptor status */
            uint8_t css;        /* Checksum start */
            uint16_t special;
        } fields;
    } upper;
}__attribute__((packed));`
Buffer Address: </br>
Address of the transmit descriptor in the host memory. Descriptors with a</br>
null address transfer no data. If they have the RS bit in the command byte</br>
set (TDESC.CMD), then the DD field in the status word (TDESC.STATUS) is</br>
written when the hardware processes them.</br>
0-63 存放buffer地址, 初始化一块内存地址放入</br>



查阅 Transmit Command (TDESC.CMD) Layout: </br>
![1689923679041](https://github.com/Leavaway/csnotes/assets/86211987/701508b7-d53e-46fc-9335-d3fed442cfcf)</br>
![1689923930385](https://github.com/Leavaway/csnotes/assets/86211987/36ede14b-6c4a-4d77-a219-080ce30e4e45)</br>
![1689923990423](https://github.com/Leavaway/csnotes/assets/86211987/ef6c29ff-1581-4733-90c2-c91f15fdbd02)</br>
根据上面描述把CMD设置为RS EOP来让软件获取发送后状态</br>
设置DD
Descriptor Done
Indicates that the descriptor is finished and is written back either after the descriptor
has been processed (with RS set) or for the 82544GC/EI, after the packet has been
transmitted on the wire (with RPS set).
//遇到了大整数隐式截断为无符号整型错误</br>


设置TDBAL</br>
![1689928909437](https://github.com/Leavaway/csnotes/assets/86211987/40536acc-cea7-4bfd-99a4-2c28bd99990f)</br>
因为是32位系统 用不到TDLEH 设置为0</br>
设置TDLEN</br>
![1689930850091](https://github.com/Leavaway/csnotes/assets/86211987/199661cb-83c5-40b5-bcf1-63e62f93f08c)</br>
设置TDH</br>
![1689931365530](https://github.com/Leavaway/csnotes/assets/86211987/16a1f706-0256-4eab-8240-e85f1cb834d4)</br>
设置TCTL</br>
 Initialize the Transmit Control Register (TCTL) for desired operation to include the following:
• Set the Enable (TCTL.EN) bit to 1b for normal operation.
• Set the Pad Short Packets (TCTL.PSP) bit to 1b
• Configure the Collision Threshold (TCTL.CT) to the desired value. Ethernet standard is 10h.
This setting only has meaning in half duplex mode.
• Configure the Collision Distance (TCTL.COLD) to its expected value. For full duplex
operation, this value should be set to 40h. For gigabit half duplex, this value should be set to
200h. For 10/100 half duplex, this value should be set to 40h.
Program the Transmit IPG (TIPG) register with the following decimal values to get the minimum
legal Inter Packet Gap

![1689647325854](https://github.com/Leavaway/csnotes/assets/86211987/5c057418-58b1-428f-a7a8-c7e1b300d381)</br>
![1689932140696](https://github.com/Leavaway/csnotes/assets/86211987/d9237d17-697c-4d6f-9502-e40c2a46bdbf)</br>
设置EN开启传输并且设置包64字节长</br>
设置CT决定重传次数(在半双工时候有意义,这个字段设置了碰撞后的最大重试次数。这对于网络数据包冲突的管理非常重要)</br>
设置COLD指定CSMA/CD操作最小时间数</br>
设置TIPG指定控制数据包之间的间隔时间</br>
![1689994821046](https://github.com/Leavaway/csnotes/assets/86211987/6f554f42-7947-429c-82be-c6011cfc5160)</br>


# PartB
接受描述符
![1690015741814](https://github.com/Leavaway/csnotes/assets/86211987/70c9387b-4d6b-4839-87e0-1c5e7bee10ee)
设置RAL/RAH为52:54:00:12:34:56
![1690083457037](https://github.com/Leavaway/csnotes/assets/86211987/14147b32-502f-44d0-80b4-59b2f907b2a8)
将MTA初始化为0，The Ethernet controller provides a 4096-bit vector multicast table array that is used when all the 16
perfect filters in the Receive Address Registers (RAR) are used. MTA长512bytes
![1690083517175](https://github.com/Leavaway/csnotes/assets/86211987/549326b8-ccaa-4b4e-8f32-0d42e2bbf77e)
分配内存和设置RDBAL/RDBAH
![1690083797896](https://github.com/Leavaway/csnotes/assets/86211987/c46062b4-8bcc-484b-97a3-ca8e34c20f78)
设置RDLEN寄存器
![1690084159094](https://github.com/Leavaway/csnotes/assets/86211987/81d0422b-a50d-41cf-906d-4b429a1d2249)
初始化RDH RDT
![1690084109267](https://github.com/Leavaway/csnotes/assets/86211987/70c4c82a-0703-4e8f-8219-64981ca61a31)
设置RCTL
![1690085121328](https://github.com/Leavaway/csnotes/assets/86211987/eb40f370-991a-47b6-9915-304fac3049b3)


在微内核设计中，确实是尽量把那些不直接涉及硬件操作的功能放到用户态来实现。当需要执行某些硬件操作时，用户态进程通过系统调用来请求内核进行操作。

这样的设计可以有很多好处，包括：

安全性：用户态进程在一个受限的环境下运行，无法直接访问硬件或其他进程的内存，这能防止一个进程意外（或恶意）干扰其他进程或系统的运行。

稳定性：用户态进程可以相互隔离，一个进程的崩溃不会直接导致系统崩溃。

灵活性和可移植性：用户态进程比内核更容易修改和移植到其他操作系统或硬件平台。

但是，这样的设计也有一些缺点，其中最主要的可能是性能开销。因为每次进行系统调用都需要在用户态和内核态之间切换，这是有一定开销的。如果一个操作需要频繁地进行系统调用，那么这种开销可能会变得比较大。因此，在设计操作系统时，需要权衡这些利弊，找到最适合的设计方案。

### BUG
input bug
一开始只显示到e1000 unicast match但是没有input, 在input.c文件的receive调用的返回值length中打印验证发现length一直是-1, 说明没有收到packet
检查e1000_receive_data的实现
int e1000_receive_data(void* addr){
	int tail = e1000[E1000_RDT>>2];
	tail = (tail + 1) % REC_DESC_SIZE;
	struct e1000_rx_desc *rx_hold = &rec_desc_list[tail];
	if((rx_hold->status & E1000_TXD_STAT_DD) == E1000_TXD_STAT_DD){
		int len = rx_hold->length;
		memcpy(addr, rec_desc_buffer[tail].buffer, len);
		e1000[E1000_RDT>>2] = tail;
		return len;
	}
	return -1;
}
RDT需要在赋值之前后移//存疑
tail = (tail + 1) % REC_DESC_SIZE;







