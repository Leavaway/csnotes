打开shell使用键盘在里面输入，由shell接受数据并回显，然后解析输入的字符串，根据输入在中找到程序并运行。linux命令主要由三部分组成: command, [option], [parameter]<br/>
如何寻找: 如果不是绝对路径和相对路径的话就去env的PATH变量里面找。<br/>
设置环境变量: 1. 仅对当前终端有效: export PATH=$PATH:/ 2. 仅对当前用户有效: 把1中的文本添加到~/.bashrc(~/.bashrc 是一个在Linux和Unix系统中的隐藏文件，位于用户主目录中（~表示用户的主目录）。该文件包含了针对Bash shell的一系列配置指令和设置。Bash是Linux和Unix系统中默认的命令行解释器（shell）之一。 )中。3. 对所有用户有效: 在/etc/environment路径里面添加要设置的路径。<br/>
