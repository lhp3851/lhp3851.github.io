---
title: iOS之React-Native与原生端通信
abbrlink: 67a88861
date: 2021-04-20 21:36:02
tags:
---

## 1. 属性

### 1.1 从原生组件传递属性到 React Native

#### 1.1.1 初始化参数: initialProperties

iOS 端：

```objective-c
NSArray *imageList = @[@"http://foo.com/bar1.png",
                       @"http://foo.com/bar2.png"];

NSDictionary *props = @{@"images" : imageList};

RCTRootView *rootView = [[RCTRootView alloc] initWithBridge:bridge
                                                 moduleName:@"ImageBrowserApp"
                                          initialProperties:props];
```

Web 端：

```javascript
import React from 'react';
import {
  View,
  Image
} from 'react-native';

export default class ImageBrowserApp extends React.Component {
  renderImage(imgURI) {
    return (
      <Image source={{uri: imgURI}} />
    );
  }
  render() {
    return (
      <View>
        {this.props.images.map(this.renderImage)}
      </View>
    );
  }
}

```

#### 1.1.2 可读写参数: appProperties

```objective-c
NSArray *imageList = @[@"http://foo.com/bar3.png",
                       @"http://foo.com/bar4.png"];

rootView.appProperties = @{@"images" : imageList};
```

**可以随时更新属性，但是更新必须在主线程中进行，读取则可以在任何线程中进行。**

### 1.2 从 React Native 传递属性到原生组件

## 2. 跨端交互

React Native 允许使用跨语言的函数调用。你可以在 JS 中调用原生代码，也可以在原生代码中调用 JS。在不同端需要用不同的方法来实现相同的目的。在原生代码中我们使用事件机制来调度 JS 中的处理函数，而在 React Native 中我们直接使用原生模块导出的方法。

### 2.1 事件

从原生代码调用 React Natvie 函数。

事件很强大，它可以不需要引用直接修改 React Native 组件。但是，当你使用时要注意下面这些陷阱：

* 由于事件可以从各种地方产生，它们可能导致混乱的依赖。
* 事件共享相同的命名空间，因此你可能遇到名字冲突。冲突不会在编写代码时被探测到，因此很难排错。
* 如果你使用了同一个 React Native 组件的多个引用，然后想在事件中区分它们，name 你很可能需要在事件中同时传递一些标识（你可以使用原生视图中的reactTag作为标识）。
  
在 React Native 中嵌入原生组件时，通常的做法是用原生组件的 RCTViewManager 作为视图的代理，通过 bridge 向 JS 发送事件。这样可以集中在一处调用相关的事件。

### 2.2 原生模块

从 React Native 中调用原生方法。

原生模块是 JS 中也可以使用的 Objective-C 类。一般来说这样的每一个模块的实例都是在每一次通过 JS bridge 通信时创建的。他们可以导出任意的函数和常量给 React Native。相关细节可以参阅这篇文章。

事实上原生模块的单实例模式限制了嵌入。假设我们有一个 React Native 组件被嵌入了一个原生视图，并且我们希望更新原生的父视图。使用原生模块机制，我们可以导出一个函数，不仅要接收预设参数，还要接收父视图的标识。这个标识将会用来获得父视图的引用以更新父视图。那样的话，我们需要维持模块中标识到原生模块的映射。虽然这个解决办法很复杂，它仍被用在了管理所有 React Native 视图的RCTUIManager类中，

## 3. 布局计算流

### 3.1 在 React Native 中嵌入一个原生组件：[iOS 原生UI组件](https://www.react-native.cn/docs/native-components-ios)

### 3.2 在原生中嵌入一个 React Native 组件

#### 3.2.1 固定大小的 React Native 内容

flexbox 是最简单的办法。

#### 3.2.2 弹性大小的 React Native

有时候我们需要渲染一些不知道大小的内容。假设尺寸将会在 JS 中动态指定。我们有两个解决办法。

* 你可以将 React Native 视图包裹在ScrollView中。这样可以保证你的内容总是可以访问，并且不会和原生视图重叠。
* React Native 允许你在 JS 中决定 RN 应用的尺寸，并且将它传递给宿主视图RCTRootView。然后宿主视图将重新布局子视图，保证 UI 统一。我们通过RCTRootView的弹性模式来达到目的。

RCTRootView支持 4 种不同的弹性模式：

```objective-c
// RCTRootView.h

typedef NS_ENUM(NSInteger, RCTRootViewSizeFlexibility) {
  RCTRootViewSizeFlexibilityNone = 0,
  RCTRootViewSizeFlexibilityWidth,
  RCTRootViewSizeFlexibilityHeight,
  RCTRootViewSizeFlexibilityWidthAndHeight,
};
```

> 注意： 在 JS 和原生中都设置弹性尺寸可能导致不确定的行为。比如--不要在设置RCTRootView为RCTRootViewSizeFlexibilityWidth时同时指定最顶层的 RN 组件宽度可变（使用 Flexbox）。

> 注意： React Native 布局是通过一个单独的线程进行计算，而原生 UI 视图是通过主线程更新。这可能导致短暂的原生端和 React Native 端的不一致。
