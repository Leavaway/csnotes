# 信号
  ## 概念
   信号是一种软件中断，用于异步通知进程某个事件已经发生。一个进程可以发送信号给另一个进程，或者内核也可以发送信号给进程。信号可以被用来处理各种各样的情况，比如处理硬件异常，控制进程，以及处理用户的输入<br/>
  ## 常用信号
    SIGINT：当用户在终端中按下Ctrl+C时，该信号会被发送到前台进程。默认行为是终止进程。
    SIGQUIT：当用户在终端中按下Ctrl+\时，该信号会被发送到前台进程。默认行为是终止进程，并生成一个核心转储文件。
    SIGTERM：这是默认的、非强制性的进程终止信号。默认行为是终止进程，但是进程可以捕获这个信号，并决定自己如何响应。
    SIGKILL：这个信号用于强制终止进程。它不能被捕获、阻塞或忽略，因此在发送这个信号之后，进程一定会被终止。
    SIGSEGV：当进程进行非法的内存访问时（例如，访问了一个它没有权限访问的内存区域），内核会发送这个信号给它。默认行为是终止进程，并生成一个核心转储文件。
    SIGCHLD：当一个子进程停止或终止时，内核会发送这个信号给其父进程。默认行为是忽略这个信号，但很多进程会捕获它，以便知道其子进程何时停止。
    SIGPIPE: Broken pipe 向一个没有读端的管道写数据, 终止进程。
    SIGCONT: SIGCONT 信号用于恢复（继续）一个被停止的进程的执行。当一个被 SIGSTOP 信号停止的进程接收到 SIGCONT 信号时，它将恢复执行。
    SIGSTOP: SIGSTOP 信号用于暂停（停止）一个进程的执行。这是一个不能被阻塞、处理或忽略的信号。
 ## 信号的五种默认处理动作
    Term（终止）：这是许多信号的默认行为，例如 SIGINT、SIGQUIT、SIGTERM 等。当进程接收到这些信号时，它将终止并退出。
    Ign（忽略）：某些信号的默认行为是被忽略，例如 SIGCHLD、SIGPWR 等。当进程接收到这些信号时，如果没有为它们设置处理函数，那么这些信号将被忽略。
    Core（转储）：某些信号的默认行为是导致进程终止并产生一个 core dump 文件，例如 SIGQUIT、SIGILL、SIGABRT、SIGFPE、SIGSEGV、SIGBUS、SIGSYS、SIGTRAP 和 SIGXCPU。core dump 文件包含了进程终止时的内存映像和其他一些信息，这对于调试进程在运行时出现的问题非常有帮助。
    Stop（停止）：某些信号的默认行为是暂停进程的执行，例如 SIGSTOP、SIGTSTP、SIGTTIN 和 SIGTTOU。这些信号不能被阻塞、处理或忽略。
    Cont（继续）：SIGCONT 信号的默认行为是恢复被停止的进程的执行。这个信号也不能被阻塞、处理或忽略。
 ## 信号的状态
    信号有三种状态: 产生, 未决, 递达
    SIGKILL 和 SIGSTOP 信号不能被捕捉、阻塞或者忽略，只能执行默认动作。
 ## 常用函数
    int kill(pid_t pid, int sig);
    int raise(int sig);
    void abort(void);
    unsigned int alarm(unsigned int seconds);
    int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);//which参数: ITIMER_REAL(自然时间),ITIMER_VIRTUAL(用户时间),ITIMER_PROF(用户时间+内核时间)
    new_value参数: 
    struct itimerval {
         struct timeval it_interval; /* Interval for periodic timer */
         struct timeval it_value;    /* Time until next expiration */
    };
    struct timeval {
       time_t      tv_sec;         /* seconds */
       suseconds_t tv_usec;        /* microseconds */
    };
