![image](https://github.com/Leavaway/csnotes/assets/86211987/a04da9a8-8553-4bdb-b01e-86f97cd54eae)
## Basic conceptions
  Unix文件系统会为每个文件分配一个inode,inode中保留了对应文件的关键元数据,例如文件状态属性和指向其数据块的指针。<br/>
  数据区被划分为更大的数据块(一般是8KB大小也可能更大),文件系统在其中存储文件数据和目录元数据。目录项包含文件名和指向i节点的指针。<br/>
  如果文件系统中的多个目录项指向同一文件的i节点,则该文件称为硬链接文件<br/>
  JOS没有采用inode, 而是simply store all of a file's (or sub-directory's) meta-data within the (one and only) directory entry describing that file.<br/>

  JOS没有提供文件系统内部实现的接口而且让用户程序直接读取目录元数据简化了实现但是可能导致使得文件系统的内部布局变得难以改变。
  ### JOS disc layout and File struct
  ![image](https://github.com/Leavaway/csnotes/assets/86211987/f886f57a-73da-4634-9809-dc4cbcd31223)<br/>
  文件系统中的超级块包含一个file结构体（struct Super中的root字段），它保存文件系统根目录的元数据
  ![image](https://github.com/Leavaway/csnotes/assets/86211987/94e8f61e-0657-441a-a212-73867e30dece)<br/>
    struct File中的f_direct数据包含存储文件前10个（NDIRECT）块的块号的空间，我们称之为文件的直接索引块。对于大小不到10*4096B=40KB的小文件，使用f_direct就够了。<br/>
  但是，对于较大的文件，我们分配一个额外的磁盘块，称为文件的间接索引块，以容纳4096/4=1024个额外的块号。<br/>
  ## disk access
  在 JOS 中，为了实现对磁盘的访问，他们采用了一种非传统的方法。通常情况下，在大多数操作系统中，对磁盘的访问是通过在内核中集成 IDE 磁盘驱动程序和相应的系统调用来完成的。也就是说，文件系统需要访问磁盘时，会通过系统调用的方式通知内核，然后由内核通过磁盘驱动程序来实现对磁盘的具体操作。这种方法被称为"单体"操作系统策略。

然而，在 JOS 中，他们将 IDE 磁盘驱动程序实现为用户级文件系统环境的一部分。也就是说，他们直接在用户级环境中实现了对磁盘的访问功能，而不是通过内核中的驱动程序。这样做的好处是，可以简化内核的实现，并且使得文件系统对磁盘的访问更加直接和高效。

为了实现这种方式，JOS 需要对内核进行一些修改，让文件系统环境具有执行磁盘访问操作所需要的特权。在 x86 架构中，这是通过设置 EFLAGS 寄存器中的 IOPL 位来实现的。当 IOPL 位被设置为高权限时，用户模式下的代码就可以执行特殊的设备 I/O 指令，如 IN 和 OUT，从而直接访问磁盘。因此，为了让文件系统能够访问磁盘，JOS 只需要将文件系统环境的 IOPL 位设置为高权限即可。

值得注意的是，这种方式的实现主要依赖于轮询，即程序化 I/O（PIO）方式的磁盘访问，并且不使用磁盘中断。虽然也可以在用户模式下实现由中断驱动的设备驱动程序（例如，L3 和 L4 内核就做到了这一点），但这会更加复杂，因为需要内核来处理设备中断，并将它们分派给正确的用户模式环境。

### JOS对于内核的简化
JOS 通过提供特权来让用户级进程自行处理特定的操作，无论是磁盘访问还是异常处理，都是这种设计理念的体现。这种设计可以使得内核更加简单，而且更能有效地利用用户级进程的能力。
  

## JOS二级页表
在 JOS 中，虽然它确实使用了二级页表，但是它将整个二级页表暴露给用户模式代码，以便用户模式代码可以自己查询和解析页表条目。这就是 uvpt[] 数组的作用。这个数组在用户空间里是只读的，但它提供了对内核页表的直接视图。使用 PGNUM(addr) 计算的索引，能直接让你访问到页表条目。

uvpt[] 是从 JOS 内核中映射的页目录和页表的线性数组。PGNUM() 宏将一个线性地址转换为一个页号，然后通过索引 uvpt[]，可以直接得到页表条目。也就是说，JOS 在用户空间设置了一个页表的镜像，这使得用户空间的代码可以直接查阅页表而无需进行额外的系统调用。

所以，虽然通常我们需要先查询页目录项（PDE）才能找到页表项（PTE），但在 JOS 的 uvpt[] 设计中，已经将这个步骤合并了，让我们可以直接通过页号找到对应的页表项。


BUG

在exercise 4里面 file_get_block(struct File *f, uint32_t filebno, char **blk)
{
       // LAB 5: Your code here.
    int r;
	uint32_t * pno;
	if((r = file_block_walk(f, filebno, &pno, 1))<0){
		return r;
	}
	if((*pno) == 0){
		if((r = alloc_block())<0){
			return r;
		}
		*pno = r;
		memset(diskaddr(r),0,BLKSIZE);
		flush_block(diskaddr(r));
	}

	*blk = diskaddr(r);

	return 0;

}使用的*blk = diskaddr(r); 但是r在alloc后传给pno后clear了 所以应该吧pno传给blk。


## JOS fs env 
![image](https://github.com/Leavaway/csnotes/assets/86211987/e130dfc5-adbe-4a9f-9d57-60997a7f01eb)

## child address space
它遍历了从 UTEXT 开始，到 USTACKTOP 结束的所有页面。PGNUM(UTEXT) 和 PGNUM(USTACKTOP) 是用户地址空间的边界。

UTEXT 和 USTACKTOP 通常定义了用户地址空间中代码和数据的区域：

UTEXT 是用户文本（即代码）段开始的地址。在 JOS 中，这通常是固定的 0x00800000。

USTACKTOP 是用户栈顶部的地址。在 JOS 中，这通常是固定的 0xEEBFE000。

