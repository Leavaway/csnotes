## memory mapped
  `void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);`<br/>
   prot: 权限设置(PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE) 要操作映射区, 至少要有读权限(PROT_READ). prot权限必须要<=open的权限<br/>
   flags: MAP_SHARED/ MAP_PRIVATE 映射区数据是否会自动同步  MAP_ANONYMOS 可以设置匿名映射, 不通过文件直接映射, 只能在父子进程之间使用<br/>
   `int munmap(void *addr, size_t length);`<br/>
<img width="600" alt="1683547509846" src="https://user-images.githubusercontent.com/86211987/236819326-632a6746-6939-4acf-8ec5-4cfb5b4f52a0.png"><br/>
## memory functions
 void \*memmove(void \*dest, const void \*src, size_t n);<br/>
 note: memmove 的一个重要特性是它能够正确处理源和目标内存区域重叠的情况。如果 src 和 dest 指向的内存区域有重叠，memmove 会确保复制的结果是正确的，即使这意味着它必须以不同的顺序或使用额外的缓冲来复制字节。这与 memcpy 函数不同，memcpy 不保证能正确处理重叠的内存区域。<br/>
 
