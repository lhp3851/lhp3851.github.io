---
title: CocoaPods guideline
date: 2023-02-22 10:42:35
tags: guideline
---


## [CocoaPods使用指南](https://juejin.cn/post/7179231344147300412)

## [系统理解 iOS 库与框架](http://chuquan.me/2021/02/14/understand-ios-library-and-framework/)

### Library VS Framework

库是所有 UNIX 系统共有的，可移植；
框架是 OSX/iOS 特有的，不可移植。

为了提供对 OSX/iOS 的高级特性的支持，同时又不愿意这些特性被移植到其他平台，苹果提出了 框架 的概念。不过，从本质而言，框架是基于库实现的，可以认为框架是对库进行了封装，是一种特殊形式的库。

```sh
框架 = 库（静态库/动态库）+ .h（头文件） + bundle（资源包）
```

从本质而言，库是一个二进制文件。因此，对于 OSX/iOS 和 UNIX 而言，其具体格式也有所不同。在 OSX/iOS 中，库采用 Mach-O 格式进行存储；在 UNIX 中，库采用 ELF 格式进行存储。除此之外，库在两种操作系统中的命名后缀也有一定的差异。对于 OSX/iOS，静态库的后缀是 .a，动态库的后缀是 .dylib；在 UNIX 中，静态库的后缀是 .a，动态库的后缀是 .so。

在 OSX/iOS 中，还有一种后缀为 .tbd 的动态库。.tbd 文件本质上是一个 YAML 文本文件，其描述了需要链接的动态库信息，其主要目的是 减小应用程序的下载大小。当应用程序引用了用户设备中 /usr/lib/ 目录下的 .dylib 动态库时，会自动生成一个 .tbd 文件，其仅仅描述了项目中引用的动态库信息，因此可以减小应用程序的下载大小。具体细节见 [传送门](https://stackoverflow.com/questions/31450690/why-xcode-7-shows-tbd-instead-of-dylib)。

#### Umbrella Framework

保护伞框架（Umbrella Framework）本质上可以认为是 对普通框架进行了封装，其包含了多个框架并隐藏它们彼此之间复杂的依赖关系。举个例子，Cocoa 框架就是一个保护伞框架，其包含了三个框架：AppKit、CoreData、Foundation。

```oc
/* 
  Cocoa.h
  Cocoa Framework
  Copyright (c) 2000-2004, Apple Computer, Inc.
  All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <CoreData/CoreData.h>
```

#### Framework Bundle Structure

上文提到框架本质上就是对库进行了封装，其包含一个或多个共享库以及相关的支持文件。下面，我们分别来看看普通框架和保护伞框架的目录结构。

首先，我们需要找到框架的保存位置。事实上，框架保存在文件系统中的多个位置：

/System/Library/Frameworks：保存苹果提供的框架，如：Foundation.framework，AVFoundation.framework
/Library/Frameworks：保存第三方框架。iOS 上该目录为空。如：OpenVPN.framework，Carthage.framework。
~/Library/Frameworks：保存用户提供的框架（如果有的话）。

此外，应用程序也可能会包含自己的框架，在其 Contents/Frameworks 目录下保存了应用程序专用的框架。其实，这里对应的就是应用程序 ipa 包中的 Frameworks 目录。

#### modulemap

module.modulemap 是一个模块映射文件，能够使框架支持模块（以及子模块），在编译时也能够利用模块编译的优势进行加速。

CocoaPods 会将每个 pod 转换为 Umbrella Framework 并添加 module map 使其支持模块。因此，每个 Pod 的 Supporting File 中会有两个对应的文件：PodName-umbrella.h（Umbrella Header）、PodName.modulemap（Module Map）。

#### use_modular_headers

开启 modular headers 的本质就是将 pod 转换为 Modular（也就是支持模块），而 Modular 是可以直接在 Swift 中 import 的，不需要再经过 bridging-header 进行桥接，从而简化了 Swift 引用 OC 的方式。
