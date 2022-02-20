---
title: MediaQuery
date: 2022-02-16 09:46:33
tags: MediaQuery
---

## 1. [媒体查询](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Media_Queries/Using_media_queries)

### 1.1 媒体类型

```all```: 适用于所有设备。

```screen```: 主要用于屏幕。

```print```: 适用于在打印预览模式下在屏幕上查看的分页材料和文档。

```speech```: 主要用于语音合成器。

### 1.2 [媒体特性（功能）](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Media_Queries/Using_media_queries#%E5%AA%92%E4%BD%93%E7%89%B9%E6%80%A7)

### 1.3 [逻辑操作符](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Media_Queries/Using_media_queries#%E5%AA%92%E4%BD%93%E7%89%B9%E6%80%A7)

```and```：用于将多个媒体查询规则组合成单条媒体查询，当每个查询规则都为真时则该条媒体查询为真，它还用于将媒体功能与媒体类型结合在一起

```not```：用于否定媒体查询，如果不满足这个条件则返回true，否则返回false。 如果使用not运算符，则还必须指定媒体类型。

```only```：仅在整个查询匹配时才用于应用样式，并且对于防止较早的浏览器应用所选样式很有用。

```,```：用于将多个媒体查询合并为一个规则。类似逻辑或or运算符。

### 1.4 版本 4 中的语法改进

媒体查询4级规范对语法进行了一些改进，以使用具有“范围”类型（例如宽度或高度，减少冗余）的功能进行媒体查询。

```css
@media (max-width: 30em) { ... }
```

等价于

```css
@media (width <= 30em) { ... }
```

使用min-和max-可以测试一个在两个值之间的宽度

```css
@media (min-width: 30em) and (max-width: 50em) { ... }
```

等价于

```css
@media (30em <= width <= 50em ) { ... }
```
