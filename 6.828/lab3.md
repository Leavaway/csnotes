用户环境的代码被调用前，操作系统一共按顺序执行了以下几个函数：

　　　　* start (kern/entry.S)

　　　　* i386_init (kern/init.c)

　　　　　　　cons_init

　　　　　　　mem_init

　　　　　　　env_init

　　　　　　　trap_init （目前还未实现）

　　　　   　　env_create

　　　　   　　env_run

　　　　　　　　env_pop_tf
