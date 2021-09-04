# DCloud iOS 原生插件开发指南

[TOC]

要开发原生插件的话，首先得去 DCloud 官网下载 DCloud SDK[^DCloud-SDK]。DCloud SDK 下载下来解压后，内容如下：

```shell
|--iOSSDK    
    |-- HBuilder-Hello                  // uni-app 离线打包工程
    |-- HBuilder-ExampleDemo            // Demo 工程
    |-- HBuilder-uniPluginDemo          // uni-app 插件开发主工程 （本文档需要使用的工程）
    |-- SDK                             // 依赖库及依赖资源文件
    |-- Feature-iOS.xls                 // 功能模块与依赖库对应关系说明表格
    |-- readme.txt                      // 目录说明
```

在聊插件开发之前，先讲一点预备知识，前面三节都是预备知识。后面插件的开发过程中，会涉及到这些知识内容。

## 1. 自定义基座[^自定义基座]

自定义基座，有两种方式获取，一种是用打包工程生成，另一种是通过云打包获取。

### 1.1 [用打包工程生成自定义基座](https://ask.dcloud.net.cn/article/35485)

1. 在打包原生工程[^打包工程]里找到 control.xml 文件，在 HBuilder 节点里查看是否有这2个：` debug="true" syncDebug="true" `配置，没有的话增加上。

2. 修改打包工程的 Bundle identifier 为你 App 的 Bundle identifier

3. 在原生打包工程里找到 info.plist 文件并增加一项：`Application supports iTunes file sharing`， 值设为 `yes`。

4. 确保原生工程里`Pandora`文件夹下的apps文件夹里只有一个文件夹，并且文件夹的名称和里面的 `manifest` 的 `id` 值相同。

5. 确保 control.xml 文件里的 appid 的值和 apps 目录下的第一个文件夹的名称一致。

6. 确保 HBuilderX 里要调试的代码的 appid 和 control.xml 的appid值一致。

7. 使用 Xcode 的 Product 下的 archive 打包，然后生成ipa，并把 ipa 名称命名为：`iOS_debug.ipa`。

8. 在 uni-app 工程里主目录下新建一个名称为 unpackage 的文件夹，再在unpackage文件夹下新建一个名称为 debug 文件夹，并把生成的`iOS_debug.ipa`包放入 `debug` 文件夹下。

到这里，自定义基座就制作完成了。

要调试的话，在 HBuildX 里，找到之前 app id 相同的 uni-app 工程，点击`运行 --> 运行到手机或模拟器 --> 使用自定义基座运行（iOS）`，等待连接成功之后，然后`运行 --> 运行到手机或模拟器 --> 选择真机或者模拟器`，HBuilderX 就会用自定义基座，把 App 运行到 iOS 设备上了。

### 1.2 云打包生成自定义基座

HBuilderX 的菜单： `运行 --> 运行到手机或模拟器 --> 制作自定义基座`， 并配置好，然后点击页面右下角的`打包`，打包后有下载链接地址，下载下来的文件命名成`iOS_debug.ipa`，就是自定义基座。

要调试的话，基座下载下来后，放到项目的 `unpackage --> debug` 下目录下。

**提示1：** 配置云打包的自定义基座需要 iOS 证书与 Profile 文件。

## 2. 运行到设备上

### 2.1 Xcode

运行 uni-app 到设备上也有两种方式，一种是通过 HbuilderX 运行到设备上，另一种是通过 Xcode。

首先用 HBuilderX 打包 `uni-app`，操作路径：`发行 --> 原生 App 本地打包 --> 生成本地 App 资源`，HBuilderX 处理好之后，会在控制台输出 App 包资源的路径，得到 App 包资源后，把 App 包资源放到原生 iOS 打包工程的指定目录`Pandora/apps/`下，并修改 `control.xml` 文件的 `appid` 与 打包资源的文件夹名称相同。

然后，运行打包工程到设备上即可，运行打包工程之前，最好配置好 App 相应的信息，例如名称，icon，版本等。

### 2.2 HBuilderX

在 HBuilderX 上运行比较简单，操作路径： `运行 --> 运行到手机或模拟器 --> 选择真机或者模拟器`。

这里的运行环境，会有两个：`标准基座` 与 `自定义基座`，看开发需要，选择相应环境。

## 3. [离线打包](https://nativesupport.dcloud.net.cn/AppDocs/usesdk/ios?id=开发环境)

去到原生 iOS 打包工程，按照下面的步骤操作：

1. 这里主要是配置工程，诸如 App 名字，版本，icon，国际化等的一些信息。照着教程配置就好。

2. 配置好之后，把从 HBuilderX 打包出来的 App 包资源放到 Pandora 的 apps 文件夹下去。

3. 最后一步是打包，上面都配置好的话，就跟 iOS 原生打包一样，操作路径，在 Xcode 里：`Product --> Archive`。

**提示2：** 记得修改 contol.xml 文件里的内容，比如环境是 Debug 还是 Release。打 Release 包的话，syncDebug 配置记得去掉。

## 4. [插件开发](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios)

为了开发过程中条理清晰，开始开发之前，先区分几个概念。

插件从类型上区分，有两种类型，这根 uni-app 的发展有关，一种是 H5+插件，不过这种插件已经成为过去式了，另一种是 uni-app 插件，这种是目前 Dcloud 的推荐的。

具体的某一个插件又有两种形式，比如Dcloud SDK 里的插件工程[^插件工程]里有个`DCTestUniPlugin`插件，这个插件，提供了 `module` 和 `component` 两种形式。

1. module： 是纯功能性的插件，没有具体界面的，比如获取手机电量，地理位置等功能。
2. component：是提供iOS 或者 Android 原生界面的插件类型。

[创建工程](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=创建插件工程)，[导入插件工程](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=导入插件工程)，[配置工程](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=工程配置)都比较简单，建议大家直接看官网，照葫芦画瓢就是。

这里直接从[代码开发](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=代码实现)部分开始聊。

### 4.1 原生方法导出

iOS 中有两种方法处理方式，一种是同步的，一种是异步的。原生的方法要通过某种途径导出后，uni-app 才能使用。

#### 4.1.1 同步方法导出

```objc
// 通过宏 UNI_EXPORT_METHOD_SYNC 将同步方法暴露给 js 端
UNI_EXPORT_METHOD_SYNC(@selector(testSyncFunc:))
/// 同步方法（注：同步方法会在 js 线程执行）
/// @param options js 端调用方法时传递的参数   支持：String、Number、Boolean、JsonObject 类型
- (NSString *)testSyncFunc:(NSDictionary *)options {
    // options 为 js 端调用此方法时传递的参数
    NSLog(@"%@",options);

    /*
     可以在该方法中实现原生功能，然后直接通过 return 返回参数给 js
     */

    // 同步返回参数给 js 端  支持：NSString、NSDictionary（只能包含基本数据类型）、NSNumber 类型
    return @"success";
}
```

#### 4.1.2 异步方法导出

```objc
// 通过宏 UNI_EXPORT_METHOD 将异步方法暴露给 js 端
UNI_EXPORT_METHOD(@selector(testAsyncFunc:callback:))
/// 异步方法（注：异步方法会在主线程（UI线程）执行）
/// @param options js 端调用方法时传递的参数   支持：String、Number、Boolean、JsonObject 类型
/// @param callback 回调方法，回传参数给 js 端   支持： NSString、NSDictionary（只能包含基本数据类型）、NSNumber 类型
- (void)testAsyncFunc:(NSDictionary *)options callback:(UniModuleKeepAliveCallback)callback { 

    // options 为 js 端调用此方法时传递的参数 NSLog(@"%@",options); // 可以在该方法中实现原生能力，然后通过 callback 回调到 js 

   if (callback) {
       // 第一个参数为回传给js端的数据，第二个参数为标识，表示该回调方法是否支持多次调用，如果原生端需要多次回调js端则第二个参数传 YES;
        callback(@"success",NO);

    }
}
```

### 4.2 Hook APP事件

如果需要在 App 启动时初始化或者需要获取系统的一些事件， 需要新建一个XXXXProxy类（注意命名加前缀防止冲突），继承 NSObject 遵守UniPluginProtocol协议

```objc
-(void)onCreateUniPlugin;

- (BOOL)application:(UIApplication *_Nullable)application didFinishLaunchingWithOptions:(NSDictionary *_Nullable)launchOptions;
- (void)application:(UIApplication *_Nullable)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *_Nullable)deviceToken;
- (void)application:(UIApplication *_Nullable)application didFailToRegisterForRemoteNotificationsWithError:(NSError *_Nullable)err;
- (void)application:(UIApplication *_Nullable)application didReceiveRemoteNotification:(NSDictionary *_Nullable)userInfo;
- (void)application:(UIApplication *_Nullable)application didReceiveLocalNotification:(UILocalNotification *_Nullable)notification;
- (BOOL)application:(UIApplication *_Nullable)application handleOpenURL:(NSURL *_Nullable)url;
- (BOOL)application:(UIApplication *_Nullable)app openURL:(NSURL *_Nonnull)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *_Nullable)options NS_AVAILABLE_IOS(9_0);

- (void)applicationWillResignActive:(UIApplication *)application;
- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationDidEnterBackground:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application;

- (BOOL)application:(UIApplication *_Nullable)application continueUserActivity:(NSUserActivity *_Nullable)userActivity restorationHandler:(void(^_Nullable)(NSArray * __nullable restorableObjects))restorationHandler API_AVAILABLE(ios(8.0));
```

### 4.3 性能

这种跨端的 App 本身性能问题有一定的瓶颈，所以 Dcloud 也提供了原生代码的运行线程和队列的控制。

#### 4.3.1 线程

想要在指定线程里运行原生代码，由于原生代码不一定能够一直运行在前台，所以线程也需要保活，可以这么实现`uniExecuteThread`

```objc
-(NSThread*)uniExecuteThread
{
    if ( nil == _uniExecuteThread) {
        _uniExecuteThread = [[NSThread alloc] initWithTarget:self selector:@selector(uniNewThread) object:nil];
        [_uniExecuteThread setName:@"TestUniModule"];
        [_uniExecuteThread start];
    }
    return _uniExecuteThread;
}

-(void)uniNewThread
{
    @autoreleasepool {
        NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
        [runLoop addPort:[NSMachPort port] forMode:NSRunLoopCommonModes];
        [runLoop run];
    }
}
```

#### 4.3.2 队列

想要在指定线程里运行原生代码，可以实现 `uniExecuteQueue`属性，可以在这个属性里返回一个具体的队列。

DCloud SDK 提供了插件相关的[API信息](https://nativesupport.dcloud.net.cn/NativePlugin/API/ios?id=dcunimodule)。

### 4.4 配置插件信息

选中工程中的 `HBuilder-uniPlugin-Info.plist`文件`右键->Open As->Source Code`找到`dcloud_uniplugins`节点，copy下面的内容添加到`dcloud_uniplugins`节点下，按您插件的实际信息填写对应的项

```xml
<dict>
    <key>hooksClass</key>
    <string>填写 hooksClass 类名 </string>
    <key>plugins</key>
    <array>
        <dict>
            <key>class</key>
            <string>填写 module 或 component 的类名</string>
            <key>name</key>
            <string>填写暴露给js端对应的 module 或 component 名称</string>
            <key>type</key>
            <string>填写 module 或 component</string>
        </dict>
    </array>
</dict>
```

* hooksClass：App系统方法钩子类，值是类名，是给有些插件需要在 app 启动时做初始化或者获取系统事件用的，如果没有可以不填为空
* class：module 或 component 对应的原生类名（示例中为 TestModule）
* name：module 或 component 对应的名称（注意：module 的 name 必须以插件id为前缀或和插件id相同，示例为DCTestUniPlugin-TestModule，其中 DCTestUniPlugin 为插件的id，需要保证唯一性，避免与其他插件冲突，component 的name 没有强制要求，但是也要保证唯一比如 dc-map）
* type：module 或 component （示例为module）

### 4.5 生成插件包

此步骤应该在您插件所有功能都开发完毕，并在开发工程中测试完成后进行，插件目录结构类似：

```shell
|-- 插件id                               // 插件包是一个以插件id命名的文件夹
    |-- android                         // 存放 android 插件所需要的依赖库及资源文件
    |-- ios                             // 存放 ios 插件所需要的依赖库及资源文件
    |-- package.json                    // 插件配置文件
```

`package.json` 文件是插件包的信息，[具体配置参考](https://nativesupport.dcloud.net.cn/NativePlugin/course/package?id=packagejson)，内容类似：

```json
{
    "name": "TestUniPlugin",
    "id": "DCTestUniPlugin",
    "version": "1.0.0",
    "description": "uni示例插件",
    "_dp_type": "nativeplugin",
    "_dp_nativeplugin": {
        "ios": {
            "plugins": [{
                "type": "module",
                "name": "DCTestUniPlugin-TestModule",
                "class": "TestModule"
            }, {
                "type": "component",
                "name": "dc-testmap",
                "class": "TestComponent"
            }],
            "frameworks": ["MapKit.framework"],
            "integrateType": "framework",
            "deploymentTarget": "9.0"
        }
    }
}
```

然后以`插件id`为名新建一个文件夹，将编辑好的 `package.json` 放进去，然后在文件夹中在新建一个 ios 文件夹，将生成的依赖库`DCTestUniPlugin.framework`copy 到 ios 目录下，这样我们的插件包就构建完成了。

接下来介绍一下如何使用本地原生的 iOS 插件。

## 5. uni-app 使用 iOS 原生插件

将原生插件导出来，按照要求放到 uni-app 里面去，然后在代码里，可以这么使用

```javascript
<template>
    <div>
        <button type="primary" @click="testAsyncFunc">testAsyncFunc</button>
        <button type="primary" @click="testSyncFunc">testSyncFunc</button>
    </div>
</template>

<script>
    // 首先需要通过 uni.requireNativePlugin("ModuleName") 获取 module 
    var testModule = uni.requireNativePlugin("DCTestUniPlugin-TestModule")
    export default {
        methods: {
            testAsyncFunc() {
                // 调用异步方法
                testModule.testAsyncFunc({
                        'name': 'uni-app',
                        'age': 1
                    },
                    (ret) => {
                        uni.showToast({
                            title:'调用异步方法 ' + ret,
                            icon: "none"
                        })
                    })
            },
            testSyncFunc() {
                // 调用同步方法
                var ret = testModule.testSyncFunc({
                    'name': 'uni-app',
                    'age': 1
                })

                uni.showToast({
                    title:'调用同步方法 ' + ret,
                    icon: "none"
                })
            }
        }
    }
</script>
```

写好代码后，[生成本地 App 包资源](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=导入-uni-app-资源)，[导入到插件开发工程](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=导入-uni-app-资源-1)，选择 `HBuilder Target` 运行，然后测试一下功能是否正常。

**提示 3**: 前端代码修改后重新导入资源时，需要在插件开发工程中删除之前导入的资源，同时将设备上的 App 删除，避免因为缓存问题导致加载的还是旧的资源。

## 6. 插件市场

原生插件发布到插件市场，本篇文章不涉及这部分内容，具体见[提交原生插件到Dcloud插件市场](https://nativesupport.dcloud.net.cn/NativePlugin/course/ios?id=提交插件市场)。

[^DCloud-SDK]: [Dcloud SDK](https://nativesupport.dcloud.net.cn/AppDocs/download/ios)
[^打包工程]: 打包工程是指 Dcloud SDK 目录下的 `HBuilder-Hello` iOS 原生项目。
[^插件工程]: 插件工程是指 Dcloud SDK 目录下的 `HBuilder-uniPluginDemo` iOS 原生项目
[^自定义基座]: [自定义基座](https://ask.dcloud.net.cn/article/35115)
