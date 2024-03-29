## 基础
   Linux系统架构: <br/>
   <img width="600" alt="1681473509464" src="https://user-images.githubusercontent.com/86211987/232037639-6ce4a24a-e13a-4062-964b-f18357995f5d.png"><br/>
## 分区
  定义: 分区是对硬盘的一种格式化。通过创建分区可以设置硬盘的各项物理参数。<br/>
  格式:<br/>
    1. FAT16: 最大支持2GB, 硬盘利用率低<br/>
    2. FAT32: 在不超过8GB的分区中，采用FAT32分区格式的每一个簇容量都固定为4kb，可以减少硬盘空间的浪费，提高利用率，但是由于文件分配表的扩大，速度比16的慢。<br/>
    3. NTFS: 不易产生碎片，且可恢复文件系统。通过标准的事务处理日志和恢复技术，可保证一致性且支持压缩<br/>
## shell
打开shell使用键盘在里面输入，由shell接受数据并回显，然后解析输入的字符串，根据输入在中找到程序并运行。linux命令主要由三部分组成: command, [option], [parameter]<br/>
如何寻找: 如果不是绝对路径和相对路径的话就去env的PATH变量里面找。<br/>
设置环境变量: 1. 仅对当前终端有效: export PATH=$PATH:/ 2. 仅对当前用户有效: 把1中的文本添加到~/.bashrc(~/.bashrc 是一个在Linux和Unix系统中的隐藏文件，位于用户主目录中（~表示用户的主目录）。该文件包含了针对Bash shell的一系列配置指令和设置。Bash是Linux和Unix系统中默认的命令行解释器（shell）之一。 )中。3. 对所有用户有效: 在/etc/environment路径里面添加要设置的路径。<br/>
终止和暂停:Ctrl+C为终止, Ctrl+Z为暂停<br/>
## GCC
  <img width="600" alt="1681185508474" src="https://user-images.githubusercontent.com/86211987/231052720-77086b3e-3fb5-4c5e-a5cc-21e35342e813.png"><br/>
  -I表示头文件搜索路径; -l表示要加载的库; -L表示要加载的库的路径<br/>
## GDB
   生成和运行: 通过gcc -g生成后用gdb运行,输入quit/q退出<br/>
   参数: set args x y; show args<br/>
   查看代码: list/l 行号/函数名/文件名:行号/文件名:函数名<br/>
   更改/查看行显示: set/show list/listsize<br/>
   设置断点: break/b 行号/函数名/文件名:行号/文件名:函数名<br/>
   查看断点: info/i break/b<br/>
   删除断点: d/del/delete 断点编号<br/>
   无效断点: disable/dis 断点编号<br/>
   生效断点: enable/ena 断点编号<br/>
   条件断点: break/b 位置 if <条件><br/>
   查看变量: print/p <br/>
   设置调试父进程或者子进程: set follow-fork-mode [parent|child]<br/>
   设置调试模式: set detach-on-fork [on|off] 默认为on, 即调式一个进程的时候, 另一个继续运行, 如果为off则挂起<br/>
   查看调试的进程: info inferiors<br/>
   切换当前调试的进程: inferior id<br/>
   使进程脱离 GDB 调试: detach inferiors id<br/>
   运行: start 停在第一行; run 停在断点; 继续运行 continue/c; 向下执行一条代码 next/n (不会进入函数体) step/s (会进入函数体) finish (跳出函数体) <br/>
         自动变量操作: display num / info display / undisplay num; 设置变量: set var (); until(需要在循环内没有断点且在循环的开始使用)<br/>
        
## 权限
例子: -rwxrwxr-x<br/>
这个字符串 -rwxrwxr-x 可以分成 10 个字符，其中第一个字符代表文件类型，接下来的九个字符分为三组，每组三个字符，分别表示文件所有者、文件所属组和其他用户的权限。让我们逐个解释这些字符：<br/>
-: 第一个字符表示文件类型。在这里，- 表示这是一个普通文件。如果是目录，这里会显示为 d，如果是符号链接，会显示为 l。<br/>
r: 第二个字符表示文件所有者的读取权限。r 代表有读取权限。<br/>
w: 第三个字符表示文件所有者的写入权限。w 代表有写入权限。<br/>
x: 第四个字符表示文件所有者的执行权限。x 代表有执行权限。<br/>
r: 第五个字符表示文件所属组的读取权限。r 代表有读取权限。<br/>
w: 第六个字符表示文件所属组的写入权限。w 代表有写入权限。<br/>
x: 第七个字符表示文件所属组的执行权限。x 代表有执行权限。<br/>
r: 第八个字符表示其他用户的读取权限。r 代表有读取权限。<br/>
-: 第九个字符表示其他用户的写入权限。- 代表没有写入权限。<br/>
x: 第十个字符表示其他用户的执行权限。x 代表有执行权限。<br/>
所以，-rwxrwxr-x 表示这是一个普通文件，文件所有者具有读取、写入和执行权限，文件所属组具有读取、写入和执行权限，其他用户具有读取和执行权限，但没有写入权限。<br/>
## 库
  概念: 库文件包含了包含供其他程序使用的函数和数据的文件。库文件分为静态库和动态库。静态库在链接阶段会被整合到可执行文件中，而动态库在程序运行时才被加载和链接。<br/>
  ### 静态库
   命名: libxxx.a<br/>
   制作: 将.o文件打包, 使用ar工具。 ar rcs libxxx.a xxx.o xxx.o(r-将文件插入备存文件中, c-建立备存文件, s-索引)<br/>
  ### 动态库
   命名: libxxx.so<br/>
   制作: gcc -c -fpic/-fPIC xx.c xx.c<br/>
         gcc -shared xx.o xx.o -o libxxx.so<br/>
   fPIC: 用于生成位置无关代码, 使用全局偏移表(Global Offset Table，GOT) GOT储存了全局变量和函数的地址。当动态库被加载到内存时，OS会设置一个重定向寄存器，指向GOT。<br/>
   动态库中的相对地址被用来更新GOT，将偏移量转换为实际地址，然后存储在GOT中。程序使用重定向寄存器找到 GOT，从中读取函数 x 的实际地址，然后跳转到该地址执行函数。<br/>
   
## makefile
  格式: 目标 ...: 依赖...<br/>
            命令...<br/>
  目标: 最终要生成的文件<br/>
  依赖: 生成目标所需要的文件或者目标<br/>
  命令: 通过执行命令对依赖操作生成目标<br/>
  命令在执行前会先检查依赖存不存在，如果不存在会去后面查找有没有生成所需要的依赖<br/>
  如果依赖的生成时间比目标生成时间晚，则重新生成目标文件<br/>
  变量: <br/>
    1. 自定义变量: var = value<br/>
    2. 预定义变量: AR, CC, CXX, $@(目标的完整名称), $^(所有依赖), $<(第一个依赖文件的名称)[自动变量只能在命令中使用]<br/>
    3. 获取变量的值: $(变量名)<br/>
  模式匹配: <br/>
    1. %.o:%.cpp<br/>
        g++ -c $< -o $@<br/>
  函数:<br/>
    1.$(wildcard PATTERN):匹配符合pattern类型的文件<br/>
    2.$(patsubst <pattern>,<replacement>,<text>):用pattern匹配text并且换成replacement<br/>
  伪目标:.PHONY,用于告诉make哪些目标不是真正的文件,确保指定的目标总是被执行，而不会因为存在一个同名文件而被跳过<br/>


    
