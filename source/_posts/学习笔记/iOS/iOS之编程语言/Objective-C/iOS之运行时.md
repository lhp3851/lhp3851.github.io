---
title: iOS之运行时
date: 2021-04-20 21:36:02
tags:  
---

## 1. class、objc_getClass、object_getClass 的区别

### 1.1 class

每次返回的结果都一样

### 1.2 objc_getClass

```objective-c
OBJC_EXPORT Class _Nullable objc_getClass(const char * _Nonnull name)
```

通过一个字符串返回一个对象，这个对象就是一个类对象，不管重复去调用几次objc_getClass这个方法

### 1.3 object_getClass

```objective-c
OBJC_EXPORT Class _Nullable object_getClass(id _Nullable obj) 
```

获取对象的类类型
