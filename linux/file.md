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
   
    
