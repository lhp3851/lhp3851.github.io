# JavaScript 知识点

## 1、Promise

### [使用](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Using_promises)

### [介绍](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise)

### 1.1 约定

* 在本轮 事件循环 运行完成之前，回调函数是不会被调用的。
* 即使异步操作已经完成（成功或失败），在这之后通过 then() 添加的回调函数也会被调用。
* 通过多次调用 then() 可以添加多个回调函数，它们会按照插入顺序执行。

### 1.2 链式调用的本质——函数式编程

Promise 是对象，有：promise、reason
拒绝事件（全局）：
    rejectionhandled
        当 Promise 被拒绝、并且在 reject 函数处理该 rejection 之后会派发此事件。
    unhandledrejection
        当 Promise 被拒绝，但没有提供 reject 函数来处理该 rejection 时，会派发此事件。

Promise 代表链中异步的完成

封装旧式 api：

```javascript
setTimeout(() => saySomething("10 seconds passed"), 10000);

=====>

const wait = ms => new Promise(resolve => setTimeout(resolve, ms));

wait(10000).then(() => saySomething("10 seconds")).catch(failureCallback);
```

### 1.3 异常捕获

catch

一遇到异常抛出，浏览器就会顺着promise链寻找下一个 onRejected 失败回调函数或者由 .catch() 指定的回调函数。

错误传递

## 1.4 组合

## 1.5 then() 会异步调用

传递到 then() 中的函数被置入了一个微任务队列，而不是立即执行，这意味着它是在 JavaScript 事件队列的所有运行时结束了，事件队列被清空之后，才开始执行：

```javascript
const wait = ms => new Promise(resolve => setTimeout(resolve, ms));

wait().then(() => console.log(4));
Promise.resolve().then(() => console.log(2)).then(() => console.log(3));
console.log(1); // 1, 2, 3, 4
```

### 1.6 嵌套

嵌套 Promise 是一种可以限制 catch 语句的作用域的控制结构写法。明确来说，嵌套的 catch 仅捕捉在其之前同时还必须是其作用域的 failureres，而捕捉不到在其链式以外或者其嵌套域以外的 error。如果使用正确，那么可以实现高精度的错误修复。

```javascript
doSomethingCritical()
.then(result => doSomethingOptional()
  .then(optionalResult => doSomethingExtraNice(optionalResult))
  .catch(e => {console.log(e.message)})) // 即使有异常也会忽略，继续运行;(最后会输出)
.then(() => moreCriticalStuff())
.catch(e => console.log("Critical failure: " + e.message));// 没有输出
```

2、async/await

3、CSS  布局

4、运行时
   执行机制：事件循环，宏/微任务
   宏/微任务
   多线程
   异步

   window document DOM

5、React 高阶/原理
   jsx

6、this

全局调用：window 或者 global

严格模式：undefined

函数调用：

call，apply

bind

箭头函数：call/apply、 bind 调用箭头函数，第一个参数 null

对象 this

原型链中的 this

getter/setter

构造函数：值覆盖

DOM 事件处理函数
