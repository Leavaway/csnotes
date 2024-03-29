# 命令 
  ## 内置命令
  pwd: 打印当前工作路径<br/>
  cd(因为 cd 命令需要改变当前 shell 进程的工作目录。如果 cd 是一个独立的可执行文件，那么它将在一个单独的子进程中运行，无法影响到父进程（即当前 shell）的工作目录。): 切换工作路径。 cd - 回到切换前路径<br/>
  export: 设置或显示环境变量<br/>
  unset: 删除环境变量<br/>
  alias: 为命令创建别名<br/>
  unalias: 删除命令别名<br/>
  help: 显示内置命令的帮助信息（仅限于 Bash shell）<br/>
  source: 用于在当前shell会话中读取并执行指定脚本文件中的命令<br/>
  type: 显示命令的类型，如果是可执行文件，还会打印出路径<br/>
  fg: fg命令用于将后台任务恢复到前台<br/>
  jobs: jobs命令用于列出当前shell会话中的所有后台任务<br/>
  ## 外部命令
  rmdir: 删除目录<br/>
  rm: 删除文件或者目录，-r递归删除，-f强制删除。<br/>
  ls: 列出当前路径文件。-a列出全部。 -l列出更详细信息<br/>
  mv: 移动文件和重命名<br/>
  cat: 用于连接文件并打印到标准输出设备上<br/>
  head:从头开始输出文件 -x,输出前x行<br/>
  tail:从尾开始输出文件 -x,输出后x行<br/>
  touch: 用于修改文件或者目录的时间属性，包括存取时间和更改时间。若文件不存在，系统会建立一个新的文件<br/>
  chmod: 更改权限, chmod ??? 3个?对应文件所有者（Owner）、用户组（Group）、其它用户（Other Users)。+x -x可以更改所有用户的x权限<br/>
  chown: 改变文件所有者<br/>
  find: find 目录名 选项 查找文件 -type 文件类型 -name 文件名字(支持通配符) -exec 支持shell命令 需要以\结尾 例: find \/i -type f -name "*.txt" -exec rm-rf {} \<br/>
  locate: 非实时查找，文件系统的信息提前存在一个db里面，locate从这个里面找，可以用sudo updatedb更新后查找实时内容<br/>
  grep: grep 选项 查找模式 文件名。例子: grep "abc" * -nwr: 是在当前目录和当前目录的子目录递归整词查找带有abc的文件并且显示行数<br/> 
  dd: 在 Unix 和类 Unix 系统中用于复制和转换文件。 例子: dd if=/home/ubuntu/linux/demo/a.out of=test bs=1024 count=2。<br/> 
  gzip, bzip2: 压缩解压缩文件, -d为解压缩。-k为保留原文件。<br/> 
  tar: 命令用于备份文件。-c生成文件包 -x解压，-t查看压缩文件，-z用gzip，-j用bzip2，+c是压缩+x是解压缩。例子: 压缩: tar czf test.tar.gz test.cpp；解压缩：tar xzf test.tar.gz test.cpp。 -C 指定目录<br/> 
  ifconfig: 查看网络, 设置IP。-a显示所有网卡接口，up/down 激活/关闭网卡接口，address 设置ip地址<br/> 
  <img width="600" alt="1680960420044" src="https://user-images.githubusercontent.com/86211987/230723705-0aec325b-ce34-4e5c-8c9e-12366f28ecf1.png"><br/> 
  vi: 编辑文件。+xx跳到指定行数。shift+G跳到结尾，set number/nonumber 显示/不显示行号，:xx跳到指定行，ctrl+f/b向前向后翻页。<br/> 
  x删除一个字符，dd删除一行，ndd删除n行，dw删除一个词，D删除这行后面的所有内容, o在当前行下面新增一行，u撤销上一步操作<br/> 
  yy复制当前行，nyy复制n行，p粘贴。/xx查找xx。:%s/a/b/g(c)用b替换a(替换时确认)<br/> 
  echo:在终端输出或显示文本。它通常用于显示变量的值、输出提示信息、或者将文本传递给其他命令或脚本<br/> 
  which:显示可执行文件的完整路径。用于找到命令或程序的实际位置<br/>
  whatis:显示简短的命令或程序描述。用于快速获取命令或程序的基本信息。<br/> 
  man:显示命令或程序的详细手册。提供了关于命令或程序的完整信息，包括用法、选项、例子等<br/> 
  crontab:crontab -e 编辑定时任务,比如# m h dom mon dow command<br/> 
                                      30 1,5 echo "Hello World" > /home/pi/log<br/> 
                                      指示了每天1:30和5:30执行<br/> 
          在底部加入@reboot /path/to/your/command实现开机自动<br/>
  '>' 和 '>>':重定向符号, 把一个进程的重定向输出写入文件。例: echo hello > hi.txt。如果之前不存在hi.txt则两个都是新建, 如果存在则>是覆盖, >>是加到原来存在的文件的末尾<br/>
  |:管道，变更文本流的方向，把一个进程的输出作为另一个进程的输入<br/>
  more: 类似 cat ，不过会以一页一页的形式显示，更方便使用者逐页阅读，而最基本的指令就是按空白键（space）就往下一页显示，按 b 键就会往回（back）一页显示  <br/>
  less: 与 more 类似，less 可以随意浏览文件，支持翻页和搜索，支持向上翻页和向下翻页 <br/>
  sort: 可针对文本文件的内容，以行为单位来排序  -r 以相反的顺序来排序 -n 依照数值的大小排序(-rn为按照数字降序排序) <br/>
  uniq: 用于检查及删除文本文件中重复出现的行列，一般与 sort 命令结合使用 -c或--count 在每列旁边显示该行重复出现的次数。<br/>
  head: 命令可用于查看文件的开头部分的内容，有一个常用的参数 -n 用于显示行数，默认为 10，即显示 10 行的内容<br/>
  top: 用于实时显示 process 的动态<br/>

