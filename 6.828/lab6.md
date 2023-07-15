![image](https://github.com/Leavaway/csnotes/assets/86211987/d9d6599d-995c-447f-a03c-e01d12293448)


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

### 数据包接受
In the general case, packet reception consists of recognizing the presence of a packet on the wire,
performing address filtering, storing the packet in the receive data FIFO, transferring the data to a
receive buffer in host memory, and updating the state of a receive descriptor.


### Receive Descriptor (RDESC) Layout
![1689412480700](https://github.com/Leavaway/csnotes/assets/86211987/84255d5c-9251-44fa-a357-ed0cfe8d175a)
