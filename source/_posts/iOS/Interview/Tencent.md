---
abbrlink: '0'
---
<!--
 * @Author: hepeng.l
 * @Date: 2021-05-20 10:33:40
 * @LastEditors: hepeng.l
 * @LastEditTime: 2021-05-20 10:40:39
 * @Description: 
-->

# iOS 试题

## 第一部分

1、IM模块设计
2、Block实现原理
3、包大小优化
4、卡顿优化，卡顿检测
5、埋点
6、APP优化，
7、大量数据存储、同步，
8、线上故障、
9、多线程

## 第二部分

1、苹果沙盒原理

沙盒是一种用于防止不同应用之间互相访问内容的安全机制。

2、常用存储方式

归档，plist，文件，数据库，keychain

keychain： Keychain Services 是 macOS 和 iOS 都提供一种安全地存储敏感信息的工具，keychian 依赖用于签名的provisioning profile描述文件。

3、uiview与layer

4、app共享

5、弱网优化

6、方法交换

7、请求接口拦截

8、[tableview优化](https://juejin.cn/post/6850418118850789390)

1. 避免离屏渲染；
2. 异步绘制；
3. 子线程计算；
4. 高度缓存；
5. cell 复用；
6. 图片异步加载；

9、分类调用时机

## 第三部分

1、iOS 内存管理机制 ，alloc/init 方法背后做了哪些工作？
2、什么是离屏渲染，为什么会有离屏渲染，哪些操作会造成离屏渲染，光栅化为什么形成离屏渲染？

3.2.1 什么是离屏渲染

有时因为一些限制，无法把渲染结果直接写入frame buffer，而是先暂存在另外的内存区域，之后再写入frame buffer，那么这个过程被称之为离屏渲染。也就是GPU需要在当前屏幕缓冲区以外新开辟一个缓冲区进行渲染操作。

alpha，opaque，hide，translucent；[透明度](https://developer.apple.com/documentation/uikit/uiview/1622417-alpha)

layer 用 opacity，UIview 用 alpha，alpha 的值范围从 0.0（translucent）~ 1.0（opaque）

shouldRasterize 处理圆角；
shadowPath 处理阴影；

3.2.3 哪些操作会造成离屏渲染

mask（遮罩）、
shadow（阴影）、
shouldRasterize（光栅化）、
edge antialiasing（抗锯齿）、
group opacity（不透明）、
复杂形状设置圆角等、
渐变

3、UI布局方式，autolayout 如何获取真实 frame，何时能拿到真实的frame，storyboard 合并冲突如何解决？
4、TCP和UDP协议的区别，TCP协议的四次挥手，半连接状态超时会怎样？
5、Instrument 的使用
6、runtime 在项目中的应用
7、冷启动优化
