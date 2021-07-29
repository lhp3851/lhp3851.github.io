---
title: iOS之dyld环境变量介绍
abbrlink: 10329bb4
date: 2021-04-20 21:36:02
tags:
---
## [Xcode - 使用 dyld 环境变量进行调试](https://blog.csdn.net/lovechris00/article/details/82290773)

一、使用 `DYLD_PRINT_STATISTICS` 获取启动时间

edit scheme -> run -> arguments里面加入环境变量 DYLD_PRINT_STATISTICS = 1

```shell
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
```

二、DYLD_PRINT 变量列表

* 在终端通过命令：man dyld 可以列出所有的

```shell
DYLD_FRAMEWORK_PATH
DYLD_FALLBACK_FRAMEWORK_PATH
DYLD_VERSIONED_FRAMEWORK_PATH
DYLD_LIBRARY_PATH
DYLD_FALLBACK_LIBRARY_PATH
DYLD_VERSIONED_LIBRARY_PATH
DYLD_PRINT_TO_FILE
DYLD_SHARED_REGION
DYLD_INSERT_LIBRARIES
DYLD_FORCE_FLAT_NAMESPACE
DYLD_IMAGE_SUFFIX
DYLD_PRINT_OPTS
DYLD_PRINT_ENV
DYLD_PRINT_LIBRARIES
DYLD_BIND_AT_LAUNCH
DYLD_DISABLE_DOFS
DYLD_PRINT_APIS
DYLD_PRINT_BINDINGS
DYLD_PRINT_INITIALIZERS
DYLD_PRINT_REBASINGS
DYLD_PRINT_SEGMENTS
DYLD_PRINT_STATISTICS
DYLD_PRINT_DOFS
DYLD_PRINT_RPATHS
DYLD_SHARED_CACHE_DIR
DYLD_SHARED_CACHE_DONT_VALIDATE
```

详情见：[dyld 命令简介](./dyld.txt)
