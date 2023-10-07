# 进程
  定义: 是操作系统动态执行的基本单元，在传统的操作系统中，进程既是基本的分配单元，也是基本的执行单元<br/>
        可以用一个程序来创建多个进程，进程是由内核定义的抽象实体，并为该实体分配用以执行程序的各项系统资源。从内核的角度看，进程由用户内存空间和一系列内核数据结构组成，其中用户内存空间包含了程序代码及代码所使用的变量，而内核数据结构则用于维护进程状态信息。
        记录在内核数据结构中的信息包括许多与进程相关的标识号(IDs)、虚拟内存表、打开文件的描述符表、信号传递及处理的有关信息、进程资源使用及限制、当前工作目录和大量的其他信息。<br/>
  进程控制块(PCB): 为了管理进程, 内核为每个进程分配一个PCB(Processing Control Block)以维护进程相关的信息, Linux 内核的进程控制块是 task_struct 结构体 <br/>
  进程状态: 五态模型在Linux中被广泛采用，因为它提供了足够的灵活性和简洁性，能够有效地管理进程和系统资源<br/>

 ## 查看进程: ps aux / ajx <br/>
   a: 显示终端上的所有进程, 包括其他用户的进程<br/>
   u: 显示进程的详细信息<br/>
   x: 显示没有控制终端的进程<br/>
   j: 列出与作业控制相关的信息<br/>
 ## 实时显示进程动态: top<br/>
   -d 显示信息更新的时间间隔<br/> 
   M 根据内存使用量排序<br/>  
   P 根据内CPU占有率排序<br/>  
   T 根据进程运行时间长短排序<br/> 
   U 根据用户名来筛选进程<br/> 
   K 输入指定的 PID 杀死进程<br/> 
 ## 杀死进程: kill <br/>
   [-signal] pid<br/> 
   -l 列出所有信号<br/> 
   -SIGKILL 进程ID<br/> 
   -9 进程ID<br/> 
   killall name 根据进程名杀死进程<br/> 
  ##  创建进程: fork() 
   系统调用在 UNIX 和类 UNIX 系统（如 Linux）中用于创建新的进程<br/>
   当调用 fork() 时，操作系统会创建一个新的进程，该进程是调用进程（父进程）的副本<br/>
   子进程从 fork() 处开始执行，从父进程继承其内存映像、文件描述符、栈等<br/>
   fork()使用了写时复制(Copy-On-Write): <br/>
   当fork一个子进程时，内核会为子进程创建一个新的页表，但不会立即复制父进程的整个内存地址空间。相反，内核会使子进程的页表条目指向父进程相应的物理内存页，并将这些页标记为只读(写保护)。这样，父子进程实际上共享相同的物理内存页，但各自有自己的页表。当父进程或子进程试图修改这些只读页时，COW机制/缺页异常会触发。此时，内核会为修改的进程创建一个新的物理内存页，并更新相应进程的页表条目。这样，父子进程在修改内存时才会分别拥有各自的物理内存页，实现内存隔离。<br/>
  ## exec函数族
       int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL */);
       int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
       int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] */);
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);
   execve是Linux底层系统调用, 其他的都是C库的封装函数<br/> 
   execl的pathname为路径, arg为可变参数, 一般以可执行文件名字为开头, 以NULL(哨兵)结尾<br/> 
   execlp的file为文件名, 会到环境变量中进行查找<br/> 
   l: list  p: path  v: vector  e:env<br/>  
 ## 进程退出
   `void exit(int status);`<br/>
   `void _exit(int status);`<br/>
   exit相比于_exit会多调用退出处理函数和刷新I/O缓存区, 关闭文件描述符<br/>
 ## 孤儿进程
   def: 孤儿进程（Orphan Process）是在其父进程终止后仍然继续运行的进程<br/>
   处理: 操作系统会将其所有孤儿进程的父进程更改为 init 进程。init 进程会周期性地等待其子进程结束, 以回收它们占用的资源并避免僵尸进程的产生<br/>
 ## 僵尸进程
   def: 僵尸进程（Zombie Process）是指已经完成执行并终止, 但尚未被其父进程回收资源的进程<br/>
   处理: 僵尸进程无法使用kill -9杀死, 为了避免僵尸进程, 父进程应该在子进程终止后尽快调用 wait() 或 waitpid() 系统调用来回收其资源。如果父进程在子进程终止前就已经结束，子进程会被 init 进程（进程 ID 为 1）接管<br/>
 ## 进程回收
   `pid_t wait(int *status);`允许父进程等待其一个或多个子进程的终止, 但是会阻塞父进程; status传出子进程退出的状态信息; 可以使用一些宏来检查子进程的终止状态<br/>
   `pid_t waitpid(pid_t pid, int *wstatus, int options);`pid>0为回收某子进程结束,=0为回收当前进程组所有子进程,=-1回收所有子进程(相当于wait),<-1为回收指定进程组的子进程<br/>
 ## 进程通信
   def: 进程间通信（Inter-Process Communication，IPC）是指在独立进程之间传递信息、数据的机制<br/>
   ### 管道
   1. 匿名管道: 匿名管道是一种半双工通信方式，即数据只能在一个方向上流动。它们通常用于父子进程间通信，子进程继承了父进程的文件描述符。匿名管道在文件系统中没有表示形式，因此它们只能在具有共同祖先的进程之间使用<br/>
     `int pipe(int pipefd[2]);`<br/>
     特殊情况: 当写端计数为0时再去read则返回0, 若大于0, 但写端没有往里面写数据, 读进程再read会被阻塞直到写端往里面写入数据<br/>
     当读端计数为0时再去write则该进程会受到信号SIGPIPE, 若大于0, 而持有读端的进程也没有从管道中读数据, 在管道写满时会阻塞写进程<br/>
   2. 命名管道: 命名管道，也称为FIFO（First In First Out），是一种全双工通信方式，即数据可以在两个方向上流动。与匿名管道不同，命名管道在文件系统中有表示形式，通常以特殊的设备文件形式存在。这使得没有共同祖先的进程也能进行通信<br/>
   `int mkfifo(const char *pathname, mode_t mode);`<br/>
   mode和open里面的mode是一样的<br/>
   4. 区别: FIFO 在文件系统中作为一个特殊文件存在，但 FIFO 中的内容却存放在内存中 <br/>
   当使用 FIFO的进程退出后，FIFO文件将继续保存在文件系统中以便以后使用<br/>
   FIFO有名字，不相关的进程可以通过打开有名管道进行通信<br/>
   ### 共享内存
   共享内存是一种进程间通信（IPC）的机制，允许不同的进程共享同一块内存区域。这样，多个进程可以同时访问和修改共享内存中的数据，从而达到数据共享的目的。<br/>
   
  
            
