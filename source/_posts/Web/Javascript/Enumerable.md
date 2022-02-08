---
title: Enumerable
date: 2022-02-08 17:32:13
tags: Enumerable
---


## 1. [可枚举属性和不可枚举属性](https://zhuanlan.zhihu.com/p/47291013)

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
