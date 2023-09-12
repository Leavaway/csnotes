实时操作系统: 能及时响应外部事件请求, 并能控制所有实时设备和实时任务协调运行, 且能在一个规定的时间内完成对事件的处理。分为强实时和弱实时操作系统

分时操作系统: 按照时间片完成动态任务调度

裸机系统: 将事件放在主函数中进行轮询处理, 也能实时响应任务, 用中断处理紧急任务

FreeRTOS 每个任务都有一个 typedef tskTCB TCB_t;结构体进行管理 
![1694187243449](https://github.com/Leavaway/csnotes/assets/86211987/e0a95a6c-79ed-4151-bf71-848de615a11d)

`动态创建任务:     BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,// 任务函数
                            const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const configSTACK_DEPTH_TYPE usStackDepth, // 任务栈大小
                            void * const pvParameters, // 传递给函数的参数
                            UBaseType_t uxPriority, //优先级，数字越小优先级越小
                            TaskHandle_t * const pxCreatedTask )// 就是上面的TCB_t结构体
            这个函数动态分配TCB和栈
静态创建任务:     TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                 const char * const pcName,
                                 const uint32_t ulStackDepth,
                                 void * const pvParameters,
                                 UBaseType_t uxPriority,
                                 StackType_t * const puxStackBuffer,
                                 StaticTask_t * const pxTaskBuffer );
`
在初始化任务的时候会创建pxStack从FreeRTOS一开始划分的大块heap里面分配一块内存并且初始化pxStack里面的内容，存入寄存器，把pc设置为任务函数地址，把r0设置为param的值。这样以后再调用这个任务的时候就可以直接把pc设置为&pxStack, 把param设置为&(pxStack+15)
如果在分配栈空间大小的时候过小而又在Task中使用较多内存空间的话则会导致栈溢出，在栈中内存地址由高到低增长，会影响到这个栈空间前面的部分。

任务的状态: Running/ Ready/ Blocked/ Suspended(主动/被动)
![1694246221412](https://github.com/Leavaway/csnotes/assets/86211987/398a4fd0-b5fa-454b-b76b-54178f7c44e3)
任务状态转换: vTaskResume/ vTaskSuspend/ vTaskDelay(如果想要运行+Delay总时间固定可以用vTaskDelayUtil)

任务的内存管理: 如果Task自杀则会由空闲任务(Idle Task, 在开始调度的时候系统创建)管理内存, 如果是别的任务delete则会由别的任务管理内存。
钩子函数(Idle Task Hook Functions): 空闲任务每执行一次就会执行狗子函数, 钩子函数可以用来 1) 切换系统进入省电模式 2) 测量系统的空闲时间, 计算CPU占用率 3)执行一些低优先级的, 后台的, 需要连续执行的函数
可以配置yield, 如果配置了yield则会在执行完一次while之后就让出CPU

任务调度的策略: 可以设置为抢占式调度(可以设置同优先级的任务是否交替执行)和非抢占式调度(合作调度模式)
有3种任务状态链表: pxReadyTaskList, pxDelayTaskList 和 xPendingReadyList, 其中pxReadyTaskList根据优先级设置为不同的链表比如pxReadyTaskList[0], pxReadyTaskList[1],由Tick中断进行调度

任务调度的时候需要保存现场环境: 执行位置，局部变量的值，即打断当时寄存器的值
how：压栈保存
硬件中断: 硬件帮忙在栈中保存一部分，软件保存一些处理中断需要用到的寄存器
函数调用: 不需要保存传参用的几个寄存器
任务切换: 全部寄存器都可能用到，都需要保存

栈的深度取决于局部变量和函数调用



