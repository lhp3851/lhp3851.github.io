---
title: Enumerable
date: 2022-02-20 22:02:52
tags: Enumerable
---

## 1. 属性描述对象

```js
{
  value: 123,
  writable: false,
  enumerable: true,
  configurable: false,
  get: undefined,
  set: undefined
}
```

（1）`value`

`value`是该属性的属性值，默认为`undefined`。

（2）`writable`

`writable`是一个布尔值，表示属性值（value）是否可改变（即是否可写），默认为true。

（3）`enumerable`

`enumerable`是一个布尔值，表示该属性是否可遍历，默认为true。如果设为false，会使得某些操作（比如for...in循环、Object.keys()）跳过该属性。

（4）`configurable`

`configurable`是一个布尔值，表示可配置性，默认为true。如果设为false，将阻止某些操作改写该属性，比如无法删除该属性，也不得改变该属性的属性描述对象（value属性除外）。也就是说，`configurable`属性控制了属性描述对象的可写性。

（5）`get`

`get`是一个函数，表示该属性的取值函数（getter），默认为`undefined`。

（6）`set`

`set`是一个函数，表示该属性的存值函数（setter），默认为`undefined`。

## 2. [JavaScript 可枚举属性和不可枚举属性](https://zhuanlan.zhihu.com/p/47291013)

一个对象的属性，可以分为三部分：

* inherited
* enumerable
* selfOwn

### 2.1 for...in

会遍历 inherited 与 enumerable 的

### 2.2  Object.keys

会遍历 enumerable 的

### 2.3 Object.getOwnPropertyNames

会遍历 enumerable 与 selfOwn 的
