实时操作系统: 能及时响应外部事件请求, 并能控制所有实时设备和实时任务协调运行, 且能在一个规定的时间内完成对事件的处理。分为强实时和弱实时操作系统

分时操作系统: 按照时间片完成动态任务调度

裸机系统: 将事件放在主函数中进行轮询处理, 也能实时响应任务, 用中断处理紧急任务

FreeRTOS 每个任务都有一个 typedef tskTCB TCB_t;结构体进行管理 
![1694187243449](https://github.com/Leavaway/csnotes/assets/86211987/e0a95a6c-79ed-4151-bf71-848de615a11d)
动态创建任务:     BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,// 任务函数
                            const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const configSTACK_DEPTH_TYPE usStackDepth, // 任务栈大小
                            void * const pvParameters, // 传递给函数的参数
                            UBaseType_t uxPriority, //优先级
                            TaskHandle_t * const pxCreatedTask )// 就是上面的TCB_t结构体
            这个函数动态分配TCB和栈
静态创建任务:     TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                 const char * const pcName,
                                 const uint32_t ulStackDepth,
                                 void * const pvParameters,
                                 UBaseType_t uxPriority,
                                 StackType_t * const puxStackBuffer,
                                 StaticTask_t * const pxTaskBuffer );

                            
