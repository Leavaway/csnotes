# 调度
  ## 处理机调度
   基本概念: 按照某种算法选择一个进程将处理机分配给它<br/>
   三个层次: 高级调度(外存->内存, 面向作业), 中级调度(外存->内存, 面向进程), 低级调度(内存->CPU)<br/>
   七状态模型: 比五状态模型多了2个状态<br/>
     挂起就绪（Suspended Ready）：当系统资源不足或其他原因导致进程暂时无法执行时，进程可能会被挂起并从内存中换出。挂起就绪状态的进程已准备好运行，但由于被换出内存而暂时无法执行。当条件允许时，挂起就绪状态的进程会被换入内存并恢复到就绪状态。<br/>
     挂起阻塞（Suspended Blocked）：当一个阻塞的进程被换出内存时，它进入挂起阻塞状态。与挂起就绪状态相似，这个状态下的进程在等待某个事件，但由于被换出内存而无法立即执行。当等待的事件发生且进程被换入内存时，它会转到阻塞或就绪状态。<br/>
  ## 进程调度
   时机: 
     需要进程调度: 主动放弃(正常终止, 发生异常, 主动堵塞), 被动放弃(时间片用完, 有更紧急的事情需要处理, 有更高优先级进程进入队列)<br/>
     不能进行进程调度: 在处理中断时, 进程在内核程序临界区中, 原子操作中<br/>
   方式: 抢占式, 非抢占式<br/>
  ## 调度算法
   评价指标: CPU利用率, 系统吞吐量, 周转时间, 等待时间, 响应时间<br/>
   算法: 
     1. FCFS: 按照作业/进程到达先后顺序, 非抢占式, 公平, 实现简单, 对短作业不利, 不会导致饥饿<br/>
     2. SJF/SPF: 先服务时间最短的, 为非抢占, SRTN为抢占, 会导致饥饿<br/>
     3. HRRN: 非抢占式, 按照响应比[(等待时间+要求服务时间)/要求服务时间], 不会导致饥饿<br/>
     4. 时间片轮转RR: 抢占式, 公平轮流让进程执行一个时间片, 只用于进程调度, 由时钟中断来通知CPU时间已到, 不会导致饥饿<br/>
     5. 优先级调度: 非抢占(每次调度时选当前已到达且priority最高), 抢占(在新进程到达就绪队列时决定), 会导致饥饿<br/>
     6. 多级反馈队列: 抢占式, 新进程到达先进去first que, 跑完时间片还未结束则放入下一级队列队尾, 被抢占进程放入原队列队尾, 会导致饥饿<br/>