---
title: iOS编程语言之 swift Class
abbrlink: 1841
date: 2021-07-23 16:46:02
tags:
---

## 1. [What's .self, .Type and .Protocol? Understanding Swift Metatypes](https://swiftrocks.com/whats-type-and-self-swift-metatypes)

Swift 的元类[^swift-meta-type]、类、协议、运行时类型

* 类型提取

```swift
let object = Object()
type(of: object) = Object.Type
```

* Class 的元类与类

```swift
var instance: Class.Type = Class.self
```

* Protocol 的元类与协议

```swift
var instance: Protocol.protocol = Protocol.self
```

[^swift-meta-type]: [Swift 元类](https://swiftrocks.com/whats-type-and-self-swift-metatypes)
