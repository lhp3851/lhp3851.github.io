---
title: Appium 快速上手
abbrlink: 37978e5f
date: 2021-04-20 21:36:02
tags:
---
## 1. [Appium](https://appium.io/)

Appium 是一个开源的 UI 自动化测试工具，用于自动化测试 iOS、 Android 和 Windows 上的原生、移动 Web 和 Hybrid 应用。

### 1.1 Appium 的设计理念

Appium 旨在满足移动端自动化需求的理念，概述为以下四个原则：

1. 你不应该为了自动化而重新编译你的应用或以任何方式修改它。
2. 你不应该被限制在特定的语言或框架上来编写运行测试。
3. 移动端自动化框架不应该在自动化接口方面重造轮子。
4. 移动端自动化框架应该开源，在精神、实践以及名义上都该如此。

### 1.2 概念

![Appium结构图](./appium_architecture.webp)

#### 1.2.1 客户端

Appium 客户端是指支持 Appium 对 WebDriver 协议扩展一些程序库。比如 iOS 的 XCUITest Driver、Android 的 UiAutomator2 Driver。

Appium 提供了多个语言版本的[客户端程序库](https://appium.io/docs/en/about-appium/appium-clients/index.html)：Python、Ruby、Java、JavaScript、C#等。可以从[这里](https://appium.io/downloads)下载。

Driver 也支持通过插件机制 [Plugin](https://github.com/appium/appium#plugins) 对 Driver 进行功能拓展。

#### 1.2.2 服务器

Appium 是一个用 Node.js 写的服务器。

#### 1.2.3 Session

自动化过程始终在一个会话的上下文中执行，这些客户端程序库以各自的方式发起与服务器的会话，但最终都会发给服务器一个 POST /session 请求，请求中包含一个被称作「预期能力（Desired Capabilities）」的 JSON 对象。这时服务器就会开启这个自动化会话，并返回一个用于发送后续命令的会话 ID。

#### 1.2.4 Desired Capabilities

预期能力（Desired Capabilities）是一些发送给 Appium 服务器的键值对集合（比如 map 或 hash），它告诉服务器我们想要启动什么类型的自动化会话。也有许多能力（Capabilities）可以修改服务器在自动化过程中行为。例如，我们可以将 platformName 能力设置为 iOS，以告诉 Appium 我们想要 iOS 会话，而不是 Android 或者 Windows 会话。或者我们也可以设置 safariAllowPopups 能力为 true ，确保我们在 Safari 自动化会话期间可以使用 JavaScript 打开新窗口。有关 Appium 能力的完整列表，请参阅 [能力文档](https://appium.io/docs/en/writing-running-appium/caps/index.html) 。

#### 1.2.5 Appium Desktop

Appium Server 的 GUI程序、其中还包含了一个你可以查看应用程序的层级结构的 [inspector](https://github.com/appium/appium-inspector)。
可以从这里下载 [Appium Desktop](https://appium.io/downloads)。初级阶段接触这个比较多。

## 2. Appium 环境配置

## 3. 实战示例

### 3.1 iOS

### 3.2 Web

### 3.3 Flutter

参考：

1. [Appium教程](https://blog.csdn.net/qq_32502511/article/details/106082084)
2. [IOS + Appium自动化教程](https://www.jianshu.com/p/da1e00777273)
3. [基于Appium的ios自动化教程](https://zhuanlan.zhihu.com/p/474181483)

4. [Webdriver.IO](https://webdriver.io/docs/what-is-webdriverio)
5. [WebDriver](?)
6. [WebDriver](https://www.w3.org/TR/webdriver/)
