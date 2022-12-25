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

## 3. [可枚举属性和不可枚举属性](https://zhuanlan.zhihu.com/p/47291013)

什么是可枚举属性？

* 可枚举属性是指那些内部 “可枚举” 标志设置为 true 的属性。对于通过直接的赋值和属性初始化的属性，该标识值默认为即为 true。但是对于通过 Object.defineProperty 等定义的属性，该标识值默认为 false。
* 其中js中基本包装类型的原型属性是不可枚举的，如Object, Array, Number等。
* 可枚举的属性可以通过for...in循环进行遍历（除非该属性名是一个Symbol），或者通过Object.keys()方法返回一个可枚举属性的数组。

```js
Object.defineProperty(ykx, "sex", {
    value: "male",
    //是否为枚举属性
    enumerable: false
});
```

### 1.1 for...in

能遍历自己对象上的的可枚举属性和还遍历了原型上可枚举属性。

```js
function Person() {
    this.name = "Ykx";
};
Person.prototype.School = 'Tust';
Object.defineProperty(ykx, "sex", {
    value: "male",
    //是否为枚举属性
    enumerable: false
});
let ykx = new Person();

for(var p in ykx){
　　console.log(p); //name，School
}
```

### 1.2 for...of

遍历可迭代对象的值。

```js
let list = [4, 5, 6];

for (let i in list) {
   console.log(i); // "0", "1", "2",
}

for (let i of list) {
   console.log(i); // "4", "5", "6"
}
```

### 1.3 Object.keys()

Object.keys方法只能遍历自己的对象上的可枚举的属性，不能遍历自己原型上可枚举的属性。

```js
function Person() {
    this.name = "Ykx";
};
Person.prototype.School = 'Tust';
Object.defineProperty(ykx, "sex", {
    value: "male",
    //是否为枚举属性
    enumerable: false
});
let ykx = new Person();
Object.keys(ykx).forEach(function(key) {
    console.log(key) //name
});
```

### 1.4 Object.getOwnPropertyNames()

```js
function Person() {
    this.name = "Ykx";
};
Person.prototype.School = 'Tust';
Object.defineProperty(ykx, "sex", {
    value: "male",
    //是否为枚举属性
    enumerable: false
});
let ykx = new Person();
Object.getOwnPropertyNames(ykx).forEach(function(key) {
    console.log(key);//name,sex
});
```
