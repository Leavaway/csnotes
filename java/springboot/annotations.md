### @SpringBootApplication
1. 自动配置: 启用了 Spring Boot 的自动配置功能，该功能通过扫描你的应用程序的类路径，根据依赖和代码，自动配置所需的各种组件和功能
2. 组件扫描：包含了 @ComponentScan 注解，这意味着它会自动扫描应用程序中的所有组件（如：@Controller, @Service, @Repository 等注解的类）并将它们注册为 Spring Bean。
3. 启动程序: 标记了一个类作为应用程序的入口点。当运行这个类时，Spring Boot 会自动创建一个嵌入式的 Servlet 容器（如 Tomcat），并部署应用程序。
