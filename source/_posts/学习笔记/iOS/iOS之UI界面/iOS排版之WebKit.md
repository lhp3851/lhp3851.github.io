# Webkit

[TOC]

## 1. iOS与JS交互的四种方法

1. 拦截url（适用于UIWebView和WKWebView）
2. JavaScriptCore（只适用于UIWebView，iOS7+）
3. WKScriptMessageHandler（只适用于WKWebView，iOS8+）
4. WebViewJavascriptBridge（适用于UIWebView和WKWebView，属于第三方框架）

### 1.1 方法一

（1）web调用原生：

```objective-c
 - (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType{
    if ([request.URL.absoluteString hasPrefix:@"jxaction://scan"]) {
        //调用原生扫描二维码
       return NO;
    }
        return YES;
    }
```

H5 代码

```html
<a href="jxaction://scan">扫一扫(拦截url)</a>
```

（2）原生调用js

```objective-c
[self.webView stringByEvaluatingJavaScriptFromString:@"scanResult('我是扫描结果~')"];
```

### 1.2 方法二 JavaScriptCore

（1）js调用原生
1、新建类继承自NSObject（如AppJSObject）。
2、.h文件中声明一个代理并遵循JSExport，代理内的方法和js定义的方法名一致。
3、.m文件中实现2中的代理中对应的方法，可以在方法内处理事件或通知代理。

AppJSObject.h

```objective-c
#import <Foundation/Foundation.h>
#import <JavaScriptCore/JavaScriptCore.h>

@protocol AppJSObjectDelegate <JSExport>

-(void)scan:(NSString *)message;

@end

@interface AppJSObject : NSObject<AppJSObjectDelegate>

@property(nonatomic,weak) id<AppJSObjectDelegate> delegate;

@end

```

AppJSObject.m

```objective-c
#import "AppJSObject.h"

@implementation AppJSObject

-(void)scan:(NSString *)message{
    [self.delegate scan:message];
}

@end
```

H5代码：

```html
<input type="button" name="" value="扫一扫" onclick="scan()">
<br/>
<p id="result">扫描结果：</p>

<script type="text/javascript">
    //调用APP的扫描方法   h5->app
    function scan(){
        app.scan('scanResult');
    }

    //扫描结果回调方法    app->h5
    function scanResult(result){
        document.getElementById("result").innerHTML = '扫描结果：' + result;  
    }
</script>
```

在UIWebView加载完成的代理中把AppJSObject实例对象类注入到JS中，那么在js中调用方法就会调用到原生AppJSObject实例对象中对应的方法了

```objective-c
-(void)webViewDidFinishLoad:(UIWebView *)webView
{
    JSContext *context=[webView valueForKeyPath:@"documentView.webView.mainFrame.javaScriptContext"];

    AppJSObject *jsObject = [AppJSObject new];
    jsObject.delegate = self;
    context[@"app"] = jsObject;

}
```

也可以通过block实现而不创建新类AppJSObject:

```objective-c
context[@"openAlbum"] = ^(){
    NSLog(@"js调用oc打开相册");
};
```

（2）原生调用js，可以通过一中的方法，也可以通过JSContext：

```objective-c
JSContext *context=[_mainWebView valueForKeyPath:@"documentView.webView.mainFrame.javaScriptContext"];
NSString *alertJS= [NSString stringWithFormat:@"%@('%@')",_photoMethod,fileUrl];
[context evaluateScript:alertJS];

```

### 1.3 方法三  WKScriptMessageHandler

现在很多app都是支持iOS8+，很多人使用WKWebView代替了UIWebView，但是WKWebView并不支持方法二。此时我们可以使用WKWebView的WKScriptMessageHandler

1、初始化WKWebView时，调用addScriptMessageHandler:name:方法，name为js中的方法名，如scan：

```objective-c
- (void)setupWKWebView{
    WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];
    configuration.userContentController = [[WKUserContentController alloc] init];
    [configuration.userContentController addScriptMessageHandler:self name:@"scan"];

    WKWebView *webView = [[WKWebView alloc] initWithFrame:self.view.frame configuration:configuration];
    webView.UIDelegate = self;
}
```

H5:

```html
window.webkit.messageHandlers.scan.postMessage() 
```

2、实现WKScriptMessageHandler代理方法，当js调用scan方法时，会回调此代理方法：

```objective-c
- (void)userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message{
    if ([message.name isEqualToString:@"scan"]) {
        //调用原生扫码
     }
}
```

3、原生调用js

```objective-c
[self.wkWebView evaluateJavaScript:jsString  completionHandler:^(id _Nullable result, NSError * _Nullable error) {

}];
```

注意一点，内存泄漏的情况，解决办法如下：

```objective-c
class WeakScriptMessageDelegate: NSObject, WKScriptMessageHandler {
    weak var scriptDelegate: WKScriptMessageHandler?
    
    init(_ scriptDelegate: WKScriptMessageHandler) {
        self.scriptDelegate = scriptDelegate
        super.init()
    }
    
    func userContentController(_ userContentController: WKUserContentController, didReceive message: WKScriptMessage) {
        scriptDelegate?.userContentController(userContentController, didReceive: message)
    }
    
    deinit {
        print("WeakScriptMessageDelegate is deinit")
    }
}
```

定义一个代理类：

```objective-c
wkWebView.configuration.userContentController.add(WeakScriptMessageDelegate.init(self), name: <方法名>)
```

### 1.4 方法四 WebViewJavascriptBridge

是一个第三方框架，官方文档和demo都很完整，不再累赘

*GitHub地址：*[marcuswestin/WebViewJavascriptBridge](https://github.com/marcuswestin/WebViewJavascriptBridge)

*原理及源码：* [WebViewJavascriptBridge](https://github.com/ShannonChenCHN/iOSDevLevelingUp/tree/master/ReadingSourceCode/WebViewJavascriptBridgeNotes)

*微信JS：*[JS-SDK](https://qydev.weixin.qq.com/wiki/index.php?title=%E5%BE%AE%E4%BF%A1JS-SDK%E6%8E%A5%E5%8F%A3&oldid=1667)

## 2. 大前端

1、React-Native：

* [React-Native 官网](https://facebook.github.io/react-native/)
* [React-Native 中文网](https://reactnative.cn/)

2、Flutter:

* [Flutter 官网](https://flutter.dev/)
* [Flutter 中文网](https://flutterchina.club/)

3、WeeX:

* [WeeX 官网](https://weex.incubator.apache.org/)
* [WeeX 中文网](https://weex.apache.org/zh/guide/introduction.html)
