## 文件IO
   标准C库IO函数: <br/>
   <img width="600" alt="1681716334059" src="https://user-images.githubusercontent.com/86211987/232414336-29666282-f9c3-49ff-af13-335d3b92d3dd.png"><br/>
   区别: 当追求效率时使用标准C库IO函数因为它提供了缓冲区, 可以减少磁盘IO次数; 当追求时效时使用linux IO函数，每调用一次都会进行磁盘IO<br/>
   文件描述符(File Descriptor): 是一个整数，用于表示程序访问已打开文件或其他I/O资源（如套接字、管道等）的标识符。在程序中，文件描述符通常以非负整数表示<br/>
## 文件链接
   硬链接(Hard link):ln a b;unlink a b<br/>
   软链接(Soft link):ln -s a b <br/>
## IO函数
    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);
   pathname为文件路径, flags为用于指定文件打开的方式和行为的标志, <mode> 当使用 O_CREAT 标志创建文件时，此参数用于设置新文件的权限, flags和mode都是位掩码。返回file descriptor<br/>
    ```ssize_t read(int fd, void *buf, size_t count);```<br/>
   ```ssize_t write(int fd, const void *buf, size_t count);``` <br/>
   fd为file descriptor, buf为一个指向缓冲区的指针, count为表示要从文件中读取或写入的字节数 <br/>
    `off_t lseek(int fd, off_t offset, int whence);`<br/>
   fd为file descriptor, offset为偏移量，表示要更改的文件偏移量的数值, whence指示如何解释偏移量的标志<br/>
   whence: SEEK_SET 将文件偏移量设置为 offset 字节, SEEK_CUR 将文件偏移量增加 offset 字节, SEEK_END 将文件偏移量设置为文件大小加上 offset 字节<br/>
## 文件属性
   stat: 用于获取文件或目录属性的函数<br/>
   `int stat(const char *pathname, struct stat *statbuf);`<br/>
   `int fstat(int fd, struct stat *statbuf);`<br/>
   `int lstat(const char *pathname, struct stat *statbuf);`<br/>
   <img width="600" alt="1682237407862" src="https://user-images.githubusercontent.com/86211987/233827995-a543d7cf-6787-41ab-a75e-0aedc5b5513d.png"><br/>
   `int access(const char *pathname, int mode);`<br/>
   mode: W_OK|R_OK|X_OK|F_OK<br/>
   `int chmod(const char *pathname, mode_t mode);`<br/>
   `int chown(const char *pathname, uid_t owner, gid_t group);`<br/>
   `int truncate(const char *path, off_t length);`<br/>
    truncate用于更改文件的大小<br/>
## 目录操作
   `int mkdir(const char *pathname, mode_t mode);`<br/>
   `int rename(const char *oldpath, const char *newpath);`<br/>
   `char *getcwd(char *buf, size_t size);`<br/>
   `int chdir(const char *path);`改变进程的工作目录<br/>
   `DIR *opendir(const char *name);`<br/>
   `struct dirent *readdir(DIR *dirp);`<br/>
   `int closedir(DIR *dirp);`<br/>
   direct结构体: <br/>
   <img width="600" alt="1682408129123" src="https://user-images.githubusercontent.com/86211987/234206847-fb76cca8-13d9-40c5-bf97-b263749254ec.png"><br/>
   `int dup(int oldfd);`使用最小未分配file desciptor来复制oldfd<br/>
   `int dup2(int oldfd, int newfd);`把oldfd的fd复制给newfd<br/>
   `int fcntl(int fd, int cmd, ... /* arg */ );`可以用于获取或设置文件描述符的属性、更改文件状态标志等<br/>

   
    
