---
title: 走向资深 iOS 之路
abbrlink: 8d5bf204
date: 2021-05-25 00:00:00
tags:
---

[TOC]

能力培养

> 1. **独立思考 + 系统化思维 + 前瞻性思维 [+ 人力资源管理]**
> 2. **形成一套 基础 + 流程 + 机制 + 原理 + 方案 + 作品的路径**
> 3. **多元化**

## 1. 语言

### 1.1 Objective-C

#### 1.1.1 [内存管理](./../Languages/Objective-C/MemoryManagement.md)

内存管理原则

内存管理方式

野指针、悬垂指针（腾讯方案）

僵尸代码

循环引用&内存泄漏&weak 实现

[weak 实现原理](https://www.jianshu.com/p/13c4fb1cedea)

权限修饰符： copy，assign，strong 等

对象初始化过程、对象 isa 如何获取

#### 1.1.2 Block

全局

堆

栈

内存

实现原理

#### 1.1.3 并发编程

##### 1.1.3.1 并发方式

##### 1.1.3.1.1 NSThread

##### 1.1.3.1.2 GCD（实现原理）

##### 1.1.3.1.3 NSOperation

##### 1.1.3.1.4 Pthread

##### 1.1.3.2 进程通信机制

##### 1.1.3.3 线程通信机制

##### 1.1.3.4 锁

##### 1.1.3.5 Runloop

#### 1.1.4 KVC

#### 1.1.5 KVO

#### 1.1.6 Runtime

实现原理&使用场景

方法转发流程

NSObjectProxy

#### 1.1.7 Category

#### 1.1.8 Extension

#### 1.1.9 Protocols

#### 1.1.10 通知

### 1.2 Swift

## 2. 计算机

### 2.1 操作系统

死锁及其解决方式

进线程通信

CPU 调度

内存管理方式：虚拟内存、分段、分页

中断

用户态&内核态

文件系统

* [操作系统面试考点](https://blog.csdn.net/leechow007/article/details/76284274)

### 2.2 计算机网络

HTTP[s] && 2.0

TLS

TCP

UDP

IP

WebSocket  && Socket

AFNetworking、Alamofire、Moya

弱网优化

网络认证

缓存

cookie [WKWebview]

网络安全优化

NSURLProtocolProxy

### 2.3 数据结构

哈希表

链表

树

堆

栈

图

拓扑

队列

### 2.4 算法

排序算法

查找算法

复杂度

匹配（字符串）

安全（对称、非对称）

摘要

签名

哈希 与 Dictionary 的实现

### 2.4 数据库

### 2.6 安全

逆向，反逆向

代码混淆

网络安全

## 3. iOS移动端

### 3.1 UIKit

#### 3.1.1 事件响应者链

实现

运用

#### 3.1.2 约束、布局、渲染

#### 3.1.2.1 约束

cassowary 算法

#### 3.1.2.2 布局

布局引擎

#### 3.1.2.3 渲染

渲染引擎

渲染原理

离屏渲染

图片渲染优化

### 3.2 CALayer && UIView

### 3.3 动画

[深入浅出贝塞尔曲线](https://juejin.cn/post/6995482699037147166?utm_source=gold_browser_extension)

Lottie

动画类型：帧动画，组动画，补间动画等

### 3.4 字体

### 3.5 图片

CoreImage、Graphic、Material

### 3.6 视频

## 4. 大前端

### 4.1 WKWebView

### 4.2 WebviewJavascriptBridge

### 4.3 React-Native

### 4.4 Flutter

语言 + 路由管理 + 状态管理 + 导航[混合]

## 5. 软件工程

### 5.1 设计

#### 5.1.1 设计原则

#### 5.1.2 设计模式

#### 5.1.3 方案设计

形成一套 基础 + 流程 + 机制 + 原理 + 方案 + 作品的路径。

### 5.2 框架

#### 5.2.1 iOS 官方 Framework

约束、布局、动画

#### 5.2.2 经典第三方库

### 5.3 架构

架构种类

#### 5.3.1 架构模式

MVC、MVP、MVVM

RxSwift: MVVM、Reactor、RxFeedback(状态流转-Redux，单项数据流)

#### 5.3.2 架构设计

MVVM(函数响应式编程，事件驱动架构) + 微架构(插件架构) + 微服务(远程调用)

组件化方案： URL/Protocol && Runtime/Category

### 5.4 性能优化

#### 5.4.1 卡顿优化

TableView、离屏渲染、卡死、图片资源/渲染优化

##### 5.4.2 启动优化

##### 5.4.3 网络优化

请求拦截、认证、链接建立

##### 5.4.4 电量优化

电量优化涉及 CPU/GPU 任务，网络任务，硬件功能（定位），后台/前台唤醒切换消耗（任务尽量集中化）

##### 5.4.5 包大小优化

### 5.5 函数-响应式编程

### 5.6 单元测试

Unit Test

UIUnit Test

Appiume

### 5.7 工具

XCode、Git、Pod、Jenkins、Fastlane、Charles、VSCode

LLDB

## 6. 工程化

### 6.1 组件化

#### 6.1 组件

#### 6.2 Pod

* 动静态库
* 库合并

#### 6.3 组件化

蘑菇街

CTMediator

Behive

### 6.2 Fastlane

### 6.3 Jenkins

Ruby

### 6.4 CI

Git、Pod、Shell、Jenkins、蒲公英/Fir.im、钉钉

### 6.5 XcodeServer

## 7. 杂项

### 7.1 日志

### 7.2 埋点

### 7.3 常见源码库（设计方案参考）

### 7.4 蓝牙

### 7.5 Apple Developer

IPA 签名机制

上线流程

### 7.6 相关工具

#### 7.6.1 Docker

## 8. 附加

### 8.1 后端

#### 8.1.1 PHP

#### 8.1.2 Java

#### 8.1.3 CPP

#### 8.1.4 Go

## 9. iOS 常用资源

### 9.1 网站

### 9.2 博主

### 9.3 优质资源
