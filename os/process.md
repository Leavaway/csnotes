# 进程 
  ## 基本概念
   定义: 进程是进程实体的运行过程，是系统进行资源分配和调度的一个独立单位<br/>
   组成: PCB, 程序段, 数据段<br/>
   组织形式: 链接方式, 索引方式<br/>
   特征: 动态性(最基本特征), 并发性, 独立性, 异步性, 结构性<br/>
   状态: 运行态, 就绪态, 阻塞态, 创建态, 终止态<br/>
   控制: 实现进程状态的切换，用原语实现<br/>
  ## 进程通信
   定义: 进程之间的信息共享<br/>
   方式: <br/>
    1. 共享存储: 设置一个共享空间并且互斥地访问<br/>
    2. 管道通信: 设置一个特殊的共享文件并且互斥地访问。没写满不能读，没读空不能写<br/>
    3. 消息传递: 传递结构化的消息(消息头/消息体)并且由系统提供"发送/接受原语"<br/>
    
