---
title: iOS之内存管理
abbrlink: 7f25729a
date: 2021-04-20 00:00:00
tags:
---

## 内存管理原则

1、自己生成的对象，自己持有

    alloc
    new
    copy
    mutablecopy

2、非自己生成的对象，自己也能持有

    [NSMutableArray array];
    等等

3、不再需要自己持有的对象要释放
4、非自己持有的对象无法释放

实现方式

    alloc/retain/release/dealloc
    autorelease

ARC

原则

    同非ARC原则

方式：

    __strong
    __weak
    __unsafe-unretain
    __autorelease

规则

    不能使用retain/release/retainCount/autorelease
    不能使用NSAllocateObject/NSDeallocateObject
    遵循内存管理命名规则
    dealloc
    使用@autoreleasePool代替NSAutoreleasePool
    不能使用NSZone
    对象形变量不能作为C语言结构体成员
    显示转换id 和 （void *）

属性

    assign
    strong
    copy
    retain
    unsafe_unretained
    weak 

数组

    动态数组 id __strong *array = [NSMutableArray array]
    释放

实现方式：

    __strong：自动注册到autoreleasePool中
    __weak：自动注册到autoreleasePool中，是否可weak，weak变量释放流程
    __autorelease：autorelease的方式
