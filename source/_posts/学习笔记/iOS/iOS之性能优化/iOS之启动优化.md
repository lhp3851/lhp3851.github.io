---
title: iOS之启动优化
date: 2021-04-20 21:36:02
tags:  
---
### 启动优化

1、启动优化

冷启动是指， App 点击启动前，它的进程不在系统里，需要系统新创建一个进程分配给它启动的情况。这是一次完整的启动过程。

热启动是指 ，App 在冷启动后用户将 App 退后台，在 App 的进程还在系统里的情况下，用户重新启动进入 App 的过程，这个过程做的事情非常少。

* main() 函数执行前；

* main() 函数执行后；

* 首屏渲染完成后。

#### 1、main() 函数执行前

要做启动优化，就首先要知道，APP在启动前做了些什么？iOS APP 启动的时候，会做下面几件事情：

* 加载可执行文件（Mac-o、App 的.o文件）；
* 加载动态链接库，进行rebase指针调整和bind符号绑定；
* Objc 运行时的初始化处理，包括Objc相关类的注册、category注册、selector唯一性检查等；
* 初始化，包括 +load 方法，attribute((constructor))修饰函数的调用、创建C++静态全局变量。

相应的，可以做的优化工作包括：

* 减少动态库加载。每个库本身都有依赖关系，苹果公司建议使用更少的动态库，并且建议在使用动态库的数量较多时，尽量将多个动态库进行合并。数量上，苹果公司最多可以支持 6 个非系统动态库合并为一个。

* 减少加载启动后不会去使用的类或者方法。

* +load() 方法里的内容可以放到首屏渲染完成后再执行，或使用 +initialize() 方法替换掉。因为，在一个 +load() 方法里，进行运行时方法替换操作会带来 4 毫秒的消耗。不要小看这 4 毫秒，积少成多，执行 +load() 方法对启动速度的影响会越来越大。

* 控制 C++ 全局变量的数量。

#### 2、main() 函数执行后

这阶段，主要是指从main函数之后到AppDelegate 的 `didFinishLuachingWithOptions` 方法里首屏渲染相关方法执行完成。主要包括：

* 首屏初始化所需配置文件的读写操作；
* 首屏列表大数据的读取；
* 首屏渲染的大量计算等；

对于这部分，做好结合业务和性能考虑，合理安排初始化。尽量不要阻塞主线程。

#### 3、首屏渲染完成后

这部分是指首屏渲染完成到`didFinishLuachingWithOptions`作用域结束。主要完成的是服务模块初始化、监听注册、配置文件读取等。这里分两种方式：功能级别和方法级别的启动优化。

* 功能级别的优化的思路是： main() 函数开始执行后到首屏渲染完成前只处理首屏相关的业务，其他非首屏业务的初始 化、监听注册、配置文件读取等都放到首屏渲染完成后去做。

* 在这之后，我们需要进一步做的，是检查首屏渲染完成前主线程上有哪些耗时方法，将没必要的耗时方法滞 后或者异步执行。通常情况下，耗时较长的方法主要发生在计算大量数据的情况下，具体的表现就是加载、 编辑、存储图片和文件等资源。

目前来看，对App启动速度的监控，主要有两种手段。

* 第一种方法是，定时抓取主线程上的方法调用堆栈，计算一段时间里各个方法的耗时。Xcode 工具套件里自 带的 Time Profiler ，采用的就是这种方式。
* 第二种方法是，对 objc_msgSend 方法进行 hook 来掌握所有方法的执行耗时。hook objc_msgSend 这种方式的优点是非常精确，而缺点是只能针对 Objective-C 的方法。当然，对于 c 方 法和 block 也不是没有办法，你可以使用 libffi 的 ffi_call 来达成 hook，但缺点就是编写维护相关工具门槛高。

函数执行前(DYLD_PRINT_STATISTICS=1)，耗时：

    Total pre-main time: 1.3 seconds (100.0%)
             dylib loading time: 531.35 milliseconds (39.9%)
            rebase/binding time:  46.17 milliseconds (3.4%)
                ObjC setup time: 178.40 milliseconds (13.4%)
               initializer time: 572.91 milliseconds (43.1%)
               slowest intializers :
                 libSystem.B.dylib :   8.27 milliseconds (0.6%)
        libMainThreadChecker.dylib :  42.80 milliseconds (3.2%)
              libglInterpose.dylib : 227.26 milliseconds (17.1%)
             libMTLInterpose.dylib :  40.13 milliseconds (3.0%)
                     sd_doctor_ios : 402.81 milliseconds (30.3%)

首屏出现时间——未登录： 0.4437880516052246
首屏出现时间——已登录： 0.7114208936691284/0.6743890047073364
                    end time：0.7480049133300781

第一次优化：

    show time: 0.2890850305557251
    end time: 0.5157899856567383

第二次优化：
未登录：

    show time: 0.27560102939605713
    end time: 0.27729904651641846
    mainAsynTime time: 0.3173290491104126
    asynTime time: 0.7670600414276123

已登录：

    show time: 0.3778949975967407
    end time: 0.37808406352996826
    mainAsynTime time: 0.7077310085296631
    asynTime time: 0.8228110074996948

冷启动加载时间：

    Total pre-main time: 1.0 seconds (100.0%)
             dylib loading time: 597.56 milliseconds (55.8%)
            rebase/binding time:  48.35 milliseconds (4.5%)
                ObjC setup time:  59.63 milliseconds (5.5%)
               initializer time: 364.73 milliseconds (34.0%)
               slowest intializers :
                 libSystem.B.dylib :   8.15 milliseconds (0.7%)
        libMainThreadChecker.dylib :  34.38 milliseconds (3.2%)
              libglInterpose.dylib :  80.59 milliseconds (7.5%)
             libMTLInterpose.dylib :  21.72 milliseconds (2.0%)
                     sd_doctor_ios : 320.42 milliseconds (29.9%)

启动优化总结：

    使用DYLD_PRINT_STATISTICS测试启动加载时间
    减少自定义的动态库集成
    精简原有的Objective-C类和代码
    移除静态的初始化操作
    使用更多的Swift代码
