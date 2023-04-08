# 命令 
  ## 内置命令
  pwd: 打印当前工作路径<br/>
  cd(因为 cd 命令需要改变当前 shell 进程的工作目录。如果 cd 是一个独立的可执行文件，那么它将在一个单独的子进程中运行，无法影响到父进程（即当前 shell）的工作目录。): 切换工作路径。 cd - 回到切换前路径<br/>
  export: 设置或显示环境变量<br/>
  unset: 删除环境变量<br/>
  alias: 为命令创建别名<br/>
  unalias: 删除命令别名<br/>
  type: 显示命令的类型（内置命令、外部命令或别名）<br/>
  help: 显示内置命令的帮助信息（仅限于 Bash shell）<br/>
  ## 外部命令
  rmdir: 删除目录<br/>
  rm: 删除文件或者目录，-r递归删除，-f强制删除。<br/>
  ls: 列出当前路径文件。-a列出全部。 -l列出更详细信息<br/>
  mv: 移动文件和重命名<br/>
  cat: 用于连接文件并打印到标准输出设备上<br/>
  touch: 用于修改文件或者目录的时间属性，包括存取时间和更改时间。若文件不存在，系统会建立一个新的文件<br/>
  chmod: 更改权限, chmod ??? 3个?对应文件所有者（Owner）、用户组（Group）、其它用户（Other Users。+x -x可以更改所有用户的x权限<br/>
  chown: 改变文件所有者<br/>
  find: find 目录名 选项 查找文件<br/>
  grep: grep 选项 查找模式 文件名。例子: grep "abc" * -nwr: 是在当前目录和当前目录的子目录递归整词查找带有abc的文件并且显示行数<br/> 
  dd: 在 Unix 和类 Unix 系统中用于复制和转换文件。 例子: dd if=/home/ubuntu/linux/demo/a.out of=test bs=1024 count=2。<br/> 
  gzip, bzip2: 压缩解压缩文件, -d为解压缩。-k为保留原文件。<br/> 
  tar: 命令用于备份文件。-c生成文件包 -x解压，-t查看压缩文件，-z用gzip，-j用bzip2，+c是压缩+x是解压缩。例子: 压缩: tar czf test.tar.gz test.cpp；解压缩：tar xzf test.tar.gz test.cpp。 -C 指定目录<br/> 
  ifconfig: 查看网络, 设置IP。-a显示所有网卡接口，up/down 激活/关闭网卡接口，address 设置ip地址<br/> 