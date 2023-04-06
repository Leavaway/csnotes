### Spring Bean
当谈论 Spring 框架时，Spring Bean 是一个核心概念。Spring Bean 是在 Spring 容器中管理的一个对象，它遵循了 Spring 的控制反转（Inversion of Control, IoC）和依赖注入（Dependency Injection, DI）的原则，并且由 Spring 容器进行管理和维护。这些原则有助于提高代码的解耦、可维护性和可测试性。
以下是关于 Spring Bean 的一些重要概念：
生命周期：Spring Bean 在 Spring 容器中有一个完整的生命周期，从创建到销毁。这个生命周期包含了各种回调方法，如初始化和销毁方法，这些方法可以让你在特定的阶段执行特定的操作。
作用域：Spring Bean 可以有多种作用域，如单例（singleton）、原型（prototype）、请求（request）和会话（session）。这些作用域决定了 Bean 实例在容器中的生存周期以及如何在应用程序中共享。
依赖注入：Spring Bean 支持依赖注入，这意味着一个 Bean 可以依赖于其他 Bean，而这些依赖关系是由 Spring 容器自动管理的。依赖注入可以通过构造器注入、setter 方法注入或字段注入来实现。
声明与注册：你可以通过多种方式声明和注册 Spring Bean，如通过 XML 配置文件、Java 配置类（使用 @Bean 注解）或者使用基于注解的组件扫描（如 @Component, @Service, @Repository 和 @Controller 等注解）。
自动装配（Autowiring）：Spring 容器可以自动装配 Bean 之间的依赖关系。这意味着你不需要手动设置 Bean 的依赖关系，Spring 会根据类型或名称来自动匹配并注入依赖。

### Inversion of Control


### Dependency Injection
