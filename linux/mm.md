## memory mapped
  `void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);`<br/>
   prot: 权限设置(PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE) 要操作映射区, 至少要有读权限(PROT_READ). prot权限必须要<=open的权限<br/>
   flags: MAP_SHARED/ MAP_PRIVATE 映射区数据是否会自动同步<br/>
   `int munmap(void *addr, size_t length);`<br/>
<img width="600" alt="1683547509846" src="https://user-images.githubusercontent.com/86211987/236819326-632a6746-6939-4acf-8ec5-4cfb5b4f52a0.png"><br/>
