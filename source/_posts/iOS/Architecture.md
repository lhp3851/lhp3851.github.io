---
title: iOS 架构设计
abbrlink: 20b1c088
date: 2021-04-20 00:00:00
tags:
---

## 1. 架构设计模式[^1]

### 1.1 [软件架构入门](http://www.ruanyifeng.com/blog/2016/09/software-architecture.html)

### 1.2 分层架构

```txt
1. 表现层（presentation）：用户界面，负责视觉和用户互动
2. 业务层（business）：实现业务逻辑
3. 服务层 (service): 不同业务逻辑的通用接口
4. 持久层（persistence）：提供数据，SQL 语句就放在这一层
5. 数据库（database） ：保存数据
```

### 1.3 事件驱动架构

```txt
1. 事件队列（event queue）：接收事件的入口
2. 分发器（event mediator）：将不同的事件分发到不同的业务逻辑单元
3. 事件通道（event channel）：分发器与处理器之间的联系渠道
4. 事件处理器（event processor）：实现业务逻辑，处理完成后会发出事件，触发下一步操作
```

### 1.4 微核架构

微核架构（microkernel architecture）又称为"插件架构"（plug-in architecture），指的是软件的内核相对较小，主要功能和业务逻辑都通过插件实现。

### 1.5 微服务架构

微服务架构分成三种实现模式:

```txt
1. RESTful API 模式：服务通过 API 提供，云服务就属于这一类
2. RESTful 应用模式：服务通过传统的网络协议或者应用协议提供，背后通常是一个多功能的应用程序，常见于企业内部
3. 集中消息模式：采用消息代理（message broker），可以实现消息队列、负载均衡、统一日志和异常处理，缺点是会出现单点失败，消息代理可能要做成集群
```

### 1.6 云架构

```txt
1. 处理单元：实现业务逻辑
2. 虚拟中间件：负责通信、保持sessions、数据复制、分布式处理、处理单元的部署。
```

## 2. [浅谈 MVC、MVP 和 MVVM 架构模式](https://draveness.me/mvx/)

### 2.1 MVC

### 2.2 MV-VM

## 3. RxSwift 常用架构

## 3.1. RxFeedback

## 3.2 ReactorKit

## 4. [iOS应用架构谈](https://casatwy.com/iosying-yong-jia-gou-tan-kai-pian.html)

* [今日头条：iOS 架构设计杂谈](https://juejin.cn/post/6844903623252525064)

[^1]: [MVC是框架？是设计模式？是架构？还是……](https://blog.csdn.net/CillyB/article/details/79464339?utm_source=blogxgwz7&utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-0&spm=1001.2101.3001.4242)
