1、启动优化
2、界面流畅性优化：
* [facebookarchive/AsyncDisplayKit](https://github.com/facebookarchive/AsyncDisplayKit)
* [TextureGroup/Texture](https://github.com/TextureGroup/Texture)

3、webView加载优化：
* [Tencent/VasSonic](https://github.com/Tencent/VasSonic)
* 大前端？？webView

工具：instrument -> Time Profiler

1、启动优化

冷启动是指， App 点击启动前，它的进程不在系统里，需要系统新创建一个进程分配给它启动的情况。这是一次完整的启动过程。

热启动是指 ，App 在冷启动后用户将 App 退后台，在 App 的进程还在系统里的情况下，用户重新启动进入 App 的过程，这个过程做的事情非常少。

* main() 函数执行前；

* main() 函数执行后；

* 首屏渲染完成后。


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

show time: 2.2816649675369263
end time: 2.4649089574813843

show time: 2.0265920162200928
end time: 2.031898021697998
mainAsynTime time: 4.420171022415161
asynTime time: 5.036141037940979

show time: 1.3438389301300049
end time: 1.3466030359268188
mainAsynTime time: 3.4654380083084106
asynTime time: 4.4123170375823975

启动优化总结：
    使用DYLD_PRINT_STATISTICS测试启动加载时间
    减少自定义的动态库集成
    精简原有的Objective-C类和代码
    移除静态的初始化操作
    使用更多的Swift代码


[iOS性能优化总结](https://juejin.im/post/5ace078cf265da23994ee493)

[WeRead团队博客](https://wereadteam.github.io/)

[iOS性能优化](http://www.mengyueping.com/2018/08/19/iOS_optimization_all/)