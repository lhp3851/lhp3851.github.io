---
title: iOS 之 自动布局
date: 2021-04-20 21:36:02
tags:  
---


[TOC]

## 1. 基础

| 型号                | 屏幕尺寸（inch） | 逻辑分辨率（point） | 缩放因子（scale factor） | 物理分辨率（pixel） | 像素密度（PPI） |
| ------------------- | ---------------- | ------------------- | ------------------------ | ------------------- | --------------- |
| iPhone3GS           | 3.5              | 320 * 480           | @1x                      | 320 * 480           | 163             |
| iPhone4/4s          | 3.5              | 320 * 480           | @2x                      | 640 * 960           | 326             |
| iPhone5/5s          | 4                | 320 * 568           | @2x                      | 640 * 1136          | 326             |
| iPhone6/6s          | 4.7              | 375 * 667           | @2x                      | 750 * 1334          | 326             |
| iPhone6Plus/6s Plus | 5.5              | 414 * 736           | @3x                      | 1242 * 2208         | 401             |

物理分辨率、逻辑分辨率、像素密度：

```latex
PPI = 根号(X*X + Y*Y) / Inch = 163 pixcel/inch
    
scale= 单位长度内的数量比(pixel/point)
```

## 2. Frame

* bounds
* frame
* anchor
* position

frame：与view中的frame概念相同，（x,y）subLayer左上角相对于supLayer坐标系的位置关系；width, height表示subLayer的宽度和高度。

bounds：与view中的bounds概念相同，（x,y）subLayer左上角相对于自身坐标系的关系；width, height表示subLayer的宽度和高度。

position：锚点在supLayer坐标系中的位置；

anchorPoint：锚点在自身坐标系中的相对位置，默认值为（0.5，0.5），左上角为（0，0），右下角为（1，1），其他位置以此类推；锚点都是对于自身来讲的. 确定自身的锚点,通常用于做相对的tranform变换.当然也可以用来确定位置；

规律如下

```objective-c
position.x = frame.origin.x + anchorPoint.x * frame.size.width；      

position.y = frame.origin.y + anchorPoint.y * frame.size.height；

frame.size.width = bounds.size.width

frame.size.height = bounds.size.height

frame.origin.x = anchorPoint.x * frame.size.width - position.x；

frame.origin.y = anchorPoint.y * frame.size.height - position.y；
```

## 3. 约束布局

3.1 Autolayout

引入了几个变量，一个是Top/Bottom Layout Guide（顶部/底部导航），一个是Superview.leading/Trailing Margin（左/右边缘间距）。Top Layout Guide其实是指的根视图的顶部，模拟器在竖屏下有状态栏，状态栏默认高度为20(注:导航栏与状态栏高度不同，导航栏的竖屏默认高度为44，横屏默认高度为32)，则Green View的Y坐标就是20 + 20 = 40。模拟器在横屏下没有状态栏，则Top Layout Guide.Bottom为0，则Green View的Y坐标就是20。Superview.leading Margin在竖屏时为16，横屏是为20。**这些在最新版的iOS有变化！**

**ICS：** 自身内容尺寸(Intrinsic Content Size，以下简称ICS)。

label， button， text fields等都是有ICS的，而UIView和NSView是没有ICS的。

 | View                                       | Intrinsic content size                 |
 | ------------------------------------------ | -------------------------------------- |
 | UIView and NSView                          | No intrinsic content size.             |
 | Sliders                                    | Defines only the width (iOS).          |
 | Labels, buttons, switches, and text fields | Defines both the height and the width. |
 | Text views and image views                 | Intrinsic content size can vary.       |

**CRCH：** 抗压缩抗拉伸(Compression-Resistance and Content-Hugging，以下简称CRCH)

![autolayout_hugging](resources/autolayout_hugging.png)

**原文：**[Auto Layout基本原理](https://www.jianshu.com/p/c6541ff0bdaf)

**3.2 实现方式：**

* NSLayoutConstraint

```objective-c
NSLayoutConstraint.init(item: btn,
                        attribute: NSLayoutAttribute.top,
                        relatedBy: NSLayoutRelation.equal,
                        toItem: view,
                        attribute: NSLayoutAttribute.top,
                        multiplier: 1,
                        constant: 180)
添加： NSLayoutConstraint.activate(hConstraints)
```

* NSLayoutConstraintAnchor
* VFL

| 功能         | 表达式   |
| ------------ | -------- |
| 水平方向     | H:       |
| 垂直方向     | V:       |
| Views        | [view]   |
| 关系         | >=,==,<= |
| SuperView    | \|       |
| 空间，间隙 - | -        |
| 优先级       | @value   |

```objective-c
let hMetrics = ["middleSpace": 10, "rightSpace": 20]
let hViews = ["label": label, "btn": btn]
let hVFL = "H:[label]-middleSpace-[btn]-rightSpace-|"
let hConstraints:[NSLayoutConstraint] = NSLayoutConstraint.constraints(withVisualFormat: hVFL,
                                        options: NSLayoutFormatOptions.directionLeadingToTrailing,
                                        metrics: hMetrics,
                                        views: hViews)
添加：NSLayoutConstraint.activate(hConstraints)
```

* Masonry、SnapKit
* Stack Views
* AutoLayout Xib
* [Self-Size-Cell](https://www.appcoda.com/self-sizing-cells/)

**3.3 布局过程：**

```txt
updateConstraints -> layoutSubViews -> drawRect

    |
    |
    V

约束变化 -> Deferred Layout Pass -> Run Loop

    |
    |
    V

Activating或Deactivating
设置constant或priority
添加和删除视图
```

## 4. 注意点

1、优先级：默认优先级
2、scrollView 等滚动视图添加优先级特例
3、视图先添加到俯视图上去
4、translatesAutoresizingMaskIntoConstraints 属性

参考：
1、[深入剖析Auto Layout](https://www.jianshu.com/p/d060bef3d620)
2、[WWDC 2018：高性能 Auto Layout](https://juejin.cn/post/6844903619360194568)
