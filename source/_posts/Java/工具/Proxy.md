---
title: Proxy
date: 2022-05-31 13:15:00
tags: Proxy
---

## 1. [java代码实现代理服务器不建议用来翻墙](https://www.fengma.xin/article/109)

### 1.1 设置代理服务器地址端口

Java支持以System.setProperty的方式设置http代理及端口，如下：

```java
System.setProperty("http.proxyHost", proxyHost);
System.setProperty("http.proxyPort", "" + proxyPort);
  
// 针对https也开启代理
System.setProperty("https.proxyHost", proxyHost);
System.setProperty("https.proxyPort", "" + proxyPort);
```

### 1.2 使用Proxy对象，在建立连接时注入到URLConnection即可

```java
// 初始化proxy对象
Proxy proxy = new Proxy(Proxy.Type.HTTP, new InetSocketAddress(proxyHost, proxyPort));
  
// 创建连接
URL u = new URL(url);
URLConnection conn = u.openConnection(proxy);
```
