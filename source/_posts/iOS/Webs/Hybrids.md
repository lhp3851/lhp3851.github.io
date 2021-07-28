---
title: iOS之移动端跨端技术及原理
abbrlink: 65506eb3
date: 2021-04-20 21:36:02
tags:
---

## 1. [JS-Native 通信技术](https://mp.weixin.qq.com/s/_Xo6O3NoE1z9AIMJm_uSsA)

## 1.1 postMessage （iOS WKWebview）

这种方式是在 iOS 中处理消息非常方便，但是在 Android 中并不支持。

web 端发送消息:

```javaScript
window.webkit.messageHandlers.SYJSBridge.postMessage(msg);
```

iOS 端接受消息：

```objective-c
- (void)userContentController:(WKUserContentController *)uc
didReceiveScriptMessage:(WKScriptMessage *)message
{
    // 处理消息
}
```

## 1.2 prompt（iOS、Android、WebView）

巧用 webview 的弹窗，弹窗内容定义消息体。

web 端发送消息：

```javascript
window.prompt(msg);
```

iOS 端接受消息：

```objective-c
- (void)webView:(WKWebView *)webView 
runJavaScriptTextInputPanelWithPrompt:(NSString *)prompt 
defaultText:(NSString *)defaultText 
initiatedByFrame:(WKFrameInfo *)frame 
completionHandler:(void (^)(NSString *))completionHandler
{
    completionHandler(@"OC input");
}
```

## 1.3 iframe（iOS、Android、WebView）

创建一个隐形的 iframe，Native 侧会收到一个请求，可以通过请求地址来做一个处理，达到通信的目的。

web 端发送消息：

```javascript
const callIframe = function(url) {
  var iframe = document.createElement('iframe');
  iframe.src = url;
  document.body.appendChild(iframe);
  document.body.removeChild(iframe);
}
```

iOS 端接受消息：

```objective-c
- (void)webView:(WKWebView *)webView
decidePolicyForNavigationAction:(WKNavigationAction *)na 
decisionHandler:(void (^)(WKNavigationActionPolicy))h {
    NSLog(@"%@", NSStringFromSelector(_cmd));
    decisionHandler(WKNavigationActionPolicyAllow);
}
```

## 1.4 注入 JS

  这种方式主要通过 webview 提供的 API 向 JavaScript 执行引擎中注入 JavaScript 代码。下面的代码在页面加载时注入了一个 add 函数，这个函数被挂载到了 window 下，在网页中可直接调用。

iOS 端实现：

```objective-c
WKUserScript *script = [[WKUserScript alloc] 
initWithSource:@"function add(a, b) { return a + b; }"
injectionTime:WKUserScriptInjectionTimeAtDocumentStart 
forMainFrameOnly:YES];
[webview.configuration.userContentController addUserScript:script];
```

### 1.5 location.href （iOS、Android、WebView）

这种方式和 1.3 方法类似，不过需要对做通信 API 的路由做拦截处理，否则会跳转到新的页面。

web 端发送消息：

```javascript
window.location.href = url;
```

iOS 端接受消息：

```objective-c
- (void)webView:(WKWebView *)webView 
decidePolicyForNavigationAction:(WKNavigationAction *)na 
decisionHandler:(void (^)(WKNavigationActionPolicy))d {
    NSLog(@"%@", NSStringFromSelector(_cmd));
    if ([na.request.URL.absoluteString containsString:@"suyan"]) {
        d(WKNavigationActionPolicyCancel);
    }
    else {
        d(WKNavigationActionPolicyAllow);
    }
}
```

### 1.6 addJavaScriptInterface （Android、WebView）

把一个 Java 对象注入到 JavaScript 执行环境当中，使得在 webivew 中可直接调用该方法，间接调用 Native 方法。

## 2. 常见跨端方案

### 2.1 React-Native & WeeX

#### 2.1.1 [React-Native](https://www.react-native.cn/docs/getting-started)

#### 2.1.2 [WeeX](https://weex.apache.org/zh/docs/api/weex-variable.html)

#### 2.1.3 [Hippy](https://github.com/Tencent/Hippy/blob/master/README.zh_CN.md)

### 2.2 [Flutter](https://flutterchina.club/docs/)

### 2.3 [JavaScriptCore](https://trac.webkit.org/wiki/JavaScriptCore)

#### 2.3.1 [iOS 版](https://developer.apple.com/documentation/javascriptcore)

### 2.4 [JSPatch](https://github.com/bang590/JSPatch/wiki)

### 2.5 [WKWebViewBridgeHandler](https://github.com/Lision/ELSEWHERE/blob/master/Categroy/iOS/WebViewJavascriptBridge/webview-javascript-bridge.md)

### 2.6 [Capacitor](https://capacitorjs.com/docs/v3)

#### 2.6.1 [cordova](https://capacitorjs.com/docs/v3/cordova)

#### 2.6.2 [PhoneGap](https://github.com/phonegap)

##### 2.6.2.1 参考资料

1. [PhoneGap 手机 Web 应用开发平台](https://www.oschina.net/p/phonegap?hmsr=aladdin1e1)

#### 2.6.3 [Ionic](https://ionicframework.com/docs)

### 2.7 [DCloud](https://ask.dcloud.net.cn/docs/)

### 2.8 [Xamarin](https://docs.microsoft.com/zh-cn/xamarin/)

### 2.9 PWA & 轻应用 & 小程序 等

#### 2.9.1 [PWA](https://capacitorjs.com/docs/v3/web)  

#### 2.9.2 [轻应用](https://uniapp.dcloud.io/history)

### 2.10 [QT](https://doc.qt.io/qt-6/mobiledevelopment.html)

轻应用、流应用

### 2.9.3 小程序

#### 1. [微信小程序](https://developers.weixin.qq.com/miniprogram/dev/framework/)

#### 2. [uni-app](https://uniapp.dcloud.io/)

小程序联盟

## 3. 源码解读

### 3.1 源码阅读

### 3.1.1 [JSPatch](https://github.com/bang590/JSPatch/wiki)

### 3.1.2 [WKWebViewBridgeHandler]

1. [WKWebViewBridgeHandler](https://github.com/Lision/ELSEWHERE/blob/master/Categroy/iOS/WebViewJavascriptBridge/webview-javascript-bridge.md)

2. [iOS系列之WebViewJavascriptBridge源码分析](http://www.zyiner.com/article/3)

库结构图、使用的通信技术、通讯方式

### 3.2 推荐阅读博客

* 戴明的[深入剖析 JavaScriptCore](https://ming1016.github.io/2018/04/21/deeply-analyse-javascriptcore/)
* 戴明的[深入剖析 JavaScript 编译器/解释器引擎 QuickJS](https://ming1016.github.io/2021/02/21/deeply-analyse-quickjs/)
* 戴明的[深入剖析 WebKit](https://ming1016.github.io/2017/10/11/deeply-analyse-webkit/)

## 4. 跨端常讨论的问题

### 4.1 性能

### 4.2 交互体验

### 4.3 社区（基础建筑）完备性

### 4.4 未来前景探讨

### 4.4.1 [为什么说现在 React Native 凉了？](https://www.zhihu.com/question/266630840/answer/312188874)

### 4.4.2 [Flutter 正在被悄悄放弃吗？](https://mp.weixin.qq.com/s/hDjbMSPNz_D5JeEBMEJZCA)

### 4.4.3 [Flutter 2 正式发布！](https://mp.weixin.qq.com/s/tJe2ScLgKWFTybpBtDl2TA)

### 4.5 人力/资源节省

## 5. 其他 Mobile Web 技术/方案

### 5.1 [VasSonic](https://github.com/Tencent/VasSonic/wiki)

## 6. 期待

### 6.1 [鸿蒙](https://developer.harmonyos.com/cn/documentation)

### 6.2 统一

1. 有一个统一的、通用的系统；
2. 有一门流行的统一的[元]语言：有处理前后端、脚本、硬件的能力；
3. 计算机行业基础、设计、开放标准；

* 网络协议就是个很好的概念
