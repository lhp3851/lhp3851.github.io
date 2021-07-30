---
title: iOS之异常处理
abbrlink: 3c4e9a0e
date: 2021-04-20 21:36:02
tags:
---

1、异常日志收集

* Xcode、App Store
* 第三方
* 自己收集
        跟踪异常产生的时机并捕捉、处理：上报之类
        [iOS Swift Crash的捕获](http://www.cocoachina.com/ios/20170816/20270.html)
        [漫谈iOS Crash收集框架](https://nianxi.net/ios/ios-crash-reporter.html)
        [dSYMTools](https://blog.csdn.net/wiseuc_jianghai/article/details/78031638)
        [DWARF 介绍](https://www.jianshu.com/p/20dfe4fe1b3f)[DWARF 介绍](https://www.jianshu.com/p/20dfe4fe1b3f)

2、异常日志分析

一、.dSYM

.dSYM(debugging SYMbols)又称为调试符号表，是苹果为了方便调试和定位问题而使用的一种调试方案，本质上使用的是起源于贝尔实验室的DWARF（Debugging With Attributed Record Formats），其在.xcarchive目录中的层次结构为：

```shell
.xcarchive
    --dSYMs
      |--Your.app.dSYM
        |--Contents
          |--Resources
            |--DWARF
```

二、确定符号表和崩溃日志的一致性

有了符号表文件，有了崩溃日志文件，在解析之前一定要确保二者的对应关系，否则就算按照下述步骤解析出内容也肯定是不准确的。二者的对应关系可以通过UUID来确定。

1、从崩溃日志中获取UUID

崩溃日志比较靠下的位置有个Binary Images模块，其第一行内容如下：

```log
Binary Images:
0x1f000 - 0x906fff sd_doctor_ios armv7  <eef4e325f9d6393f93e87b7ee327a5ea> /var/containers/Bundle/Application/8BEEC659-8263-4092-A2DC-EF48060BB142/sd_doctor_ios.app/sd_doctor_ios
```

从中可以看到关于你应用的若干信息：

代码段的起终地址为：0x1f000 - 0x906fff

运行你应用的CPU指令集为：armv7

应用的UUID为：687D78E2-36CC-35C3-BD39-7D5B21E281B5（不区分大小写）

2、从符号表中获取UUID

执行以下命令从符号表中提取UUID：

```shell
dwarfdump --uuid Your.app.dSYM
dwarfdump --uuid Your.app.dSYM/Contents/Resources/DWARF/Your
```

由此得到armv7指令集的UUID为：687D78E2-36CC-35C3-BD39-7D5B21E281B5（如果你的二进制文件支持多个指令集，这里会列出每个指令集对应符号表的UUID），通过和崩溃日志中的对比发现二者一致，才可进行进一步的解析操作。

三、计算崩溃符号表地址
以下面的崩溃堆栈为例：

```shell
 Thread 0:
    0   libobjc.A.dylib                   0x33f10f60 0x33efe000 + 77664
    1   Foundation                        0x273526ac 0x2734a000 + 34476
    2   Foundation                        0x27355c3e 0x2734a000 + 48190
    3   UIKit                             0x29ef9d1c 0x29bbc000 + 3398940
    4   UIKit                             0x29ef9c9a 0x29bbc000 + 3398810
    5   UIKit                             0x29ef954c 0x29bbc000 + 3396940
    6   UIKit                             0x29c3a16a 0x29bbc000 + 516458
    7   UIKit                             0x29e4b8e6 0x29bbc000 + 2685158
    8   UIKit                             0x29c3a128 0x29bbc000 + 516392
    9   Your                              0x000f0846 0xa2000 + 321606
    10  UIKit                             0x29e90fb2 0x29bbc000 + 2969522
    11  UIKit                             0x29e91076 0x29bbc000 + 2969718
    12  UIKit                             0x29e867cc 0x29bbc000 + 2926540
    13  UIKit                             0x29c9e8ea 0x29bbc000 + 927978
    14  UIKit                             0x29bc8a6a 0x29bbc000 + 51818
    15  QuartzCore                        0x295f0a08 0x295e4000 + 51720
    16  QuartzCore                        0x295ec3e0 0x295e4000 + 33760
    17  QuartzCore                        0x295ec268 0x295e4000 + 33384
    18  QuartzCore                        0x295ebc4c 0x295e4000 + 31820
    19  QuartzCore                        0x295eba50 0x295e4000 + 31312
    20  QuartzCore                        0x295e5928 0x295e4000 + 6440
    21  CoreFoundation                    0x266d0d92 0x26604000 + 839058
    22  CoreFoundation                    0x266ce44e 0x26604000 + 828494
    23  CoreFoundation                    0x266ce856 0x26604000 + 829526
    24  CoreFoundation                    0x2661c3bc 0x26604000 + 99260
    25  CoreFoundation                    0x2661c1ce 0x26604000 + 98766
    26  GraphicsServices                  0x2da1a0a4 0x2da11000 + 37028
    27  UIKit                             0x29c2a7ac 0x29bbc000 + 452524
    28  Your                              0x0024643a 0xa2000 + 1721402
    29  libdyld.dylib                     0x34484aac 0x34483000 + 6828
```

1、 符号表堆栈地址计算方式

要想利用符号表解析出崩溃对应位置，需要计算出符号表中对应的崩溃堆栈地址。而从上述堆栈中第9行可以看到，应用崩溃发生在运行时地址0x000f0846，该进程的运行时起始地址是0xa2000，崩溃处距离进程起始地址的偏移量为十进制的321606(对应十六进制为0x4E846)。三者对应关系：

```shell
0x000f0846 = 0xa2000 + 0x4E846
```

对应的公式为：

```shell
运行时堆栈地址 = 运行时起始地址 + 偏移量
```

崩溃堆栈中的起始地址和崩溃地址均为运行时地址，根据虚拟内存偏移量不变原理，只要提供了符号表TEXT段的起始地址，再加上偏移量（这里为0x4E846）就能得到符号表中的堆栈地址，即：

```shell
符号表堆栈地址 = 符号表起始地址 + 偏移量
```

2、获取符号表中的TEXT段起始地址

符号表中TEXT段的起始地址可以通过以下命令获得：

```shell
$otool -l Your.app.dSYM/Contents/Resources/DWARF/Your
```

运行结果中的片段如下：

```shell
Load command 3
      cmd LC_SEGMENT
  cmdsize 736
  segname __TEXT
    vmaddr 0x00004000
    vmsize 0x00700000
  fileoff 0
  filesize 0
  maxprot 0x00000005
  initprot 0x00000005
    nsects 10
    flags 0x0
```

其中的vmaddr 0x00004000字段即为TEXT段的起始地址。

3、计算符号表地址

由公式：

```shell
符号表堆栈地址 = 符号表起始地址 + 偏移量
```

可得：

```shell
0x52846 = 0x4E846 + 0x4000
```

即符号表中的崩溃地址为0x52846，接下来就可以根据这个地址解析出崩溃位置了。

四、崩溃信息还原

有了符号表的崩溃地址，有以下几种方式解析崩溃信息：

1、dwarfdump

命令如下：

```shell
$dwarfdump --arch armv7 Your.app.dSYM --lookup 0x52846 | grep 'Line table'
```

需要注意的是：

```shell
这里的armv7是运行设备的CPU指令集，而不是二进制文件的指令集
```

比如armv7指令集的二进制文件运行在arm64指令集的设备上，这个地方应该写arm64。

—lookup后面跟的一定是经过准确计算的符号表中的崩溃地址

使用dwarfdump解析的结果较杂乱，因此使用grep命令抓取其中关键点展示出来

运行结果如下：

```shell
Line table dir : '/data/.../Src/OBDConnectSetting/Controller'
Line table file: 'OBDFirstConnectViewController.m' line 882, column 5 with start address 0x000000000052768
```

其中第一行是编译时文件目录，第二行包含了崩溃发生的文件名称以及文件中具体行号等信息，有了这些信息就能准确定位崩溃原因啦。

2、atos

atos是另一种更加简洁的崩溃日志解析方法，使用方式如下：

```shell
$atos -o LuBao -arch armv7 0x52846
```

其执行结果如下：

```objective-c
-[OBDFirstConnectViewController showOilPricePickerView] (in Your) (OBDFirstConnectViewController.m:882)
```

相对dwarfdump命令的解析结果，更加简洁直观的指出了崩溃发生的位置。

3、无需符号表崩溃地址的解析方式

实际上，atos还提供了另外一种无需计算崩溃地址对应的符号表地址的方式，命令格式如下：

```shell
$atos -o Your.app.dSYM/Contents/Resources/DWARF/Your -arch armv7 -l 0xa2000 0x000f0846
```

其中-l选项指定了二进制文件在运行时的起始地址0xa2000（获取方式见Binary Images相关内容）,后面跟的是崩溃发生的运行时地址0x000f0846，解析结果和使用计算得到的符号表中崩溃地址一致：

```objectvie-c
-[OBDFirstConnectViewController showOilPricePickerView] (in Your) (OBDFirstConnectViewController.m:882)
```

五、参考文档

* [How to Match a Crash Report to a Build](https://developer.apple.com/library/mac/qa/qa1765/_index.html)

* [CrashReporter](https://developer.apple.com/library/mac/technotes/tn2004/tn2123.html)

* [Understanding and Analyzing iOS Application Crash Reports](https://developer.apple.com/library/ios/technotes/tn2151/_index.html)

* [atos and dwarfdump won’t symbolicate my address](http://stackoverflow.com/a/12464678/2293677)

**原文参考：**[手动解析CrashLog](http://www.cocoachina.com/ios/20150803/12806.html)

3、异常处理
4、异常规避

* 内存地址分配
* 日志源文件
* 异常产生

Linux系统中，支持两类信号

1.POSIX标准的规则信号(regular signal，编号1－31)

2.实时信号(real-time signal，编号32－63)

对于regular signal来说，无论发送多少次，在接收进程处理之前，重复的信号会被合并为一个（每一种regular signal对应于系统进程表项中软中断字段的一个比特，因此不同的信号可以同时存在，同一信号仅能表示有或无而不能表示重复的次数)；

而real-time signal发送多少次，就会在接收进程的信号队列中出现多少次。
Linux在i386上的31个规则信号(regular signal)

```shell
kill -l
```

| 编号 | 信号名称          | 缺省动作 | 说明                           |
| ---- | ----------------- | -------- | ------------------------------ |
| 1    | SIGHUP            | 终止     | 终止控制终端或进程             |
| 2    | SIGINT            | 终止     | 键盘产生的中断(Ctrl-C)         |
| 3    | SIGQUIT           | dump     | 键盘产生的退出                 |
| 4    | SIGILL            | dump     | 非法指令                       |
| 5    | SIGTRAP           | dump     | debug中断                      |
| 6    | SIGABRT／SIGIOT   | dump     | 异常中止                       |
| 7    | SIGBUS／SIGEMT    | dump     | 总线异常/EMT指令               |
| 8    | SIGFPE            | dump     | 浮点运算溢出                   |
| 9    | SIGKILL           | 终止     | 强制进程终止                   |
| 10   | SIGUSR1           | 终止     | 用户信号,进程可自定义用途      |
| 11   | SIGSEGV           | dump     | 非法内存地址引用               |
| 12   | SIGUSR2           | 终止     | 用户信号，进程可自定义用途     |
| 13   | SIGPIPE           | 终止     | 向某个没有读取的管道中写入数据 |
| 14   | SIGALRM           | 终止     | 时钟中断(闹钟)                 |
| 15   | SIGTERM           | 终止     | 进程终止                       |
| 16   | SIGSTKFLT         | 终止     | 协处理器栈错误                 |
| 17   | SIGCHLD           | 忽略     | 子进程退出或中断               |
| 18   | SIGCONT           | 继续     | 如进程停止状态则开始运行       |
| 19   | SIGSTOP           | 停止     | 停止进程运行                   |
| 20   | SIGSTP            | 停止     | 键盘产生的停止                 |
| 21   | SIGTTIN           | 停止     | 后台进程请求输入               |
| 22   | SIGTTOU           | 停止     | 后台进程请求输出               |
| 23   | SIGURG            | 忽略     | socket发生紧急情况             |
| 24   | SIGXCPU           | dump     | CPU时间限制被打破              |
| 25   | SIGXFSZ           | dump     | 文件大小限制被打破             |
| 26   | SIGVTALRM         | 终止     | 虚拟定时时钟                   |
| 27   | SIGPROF           | 终止     | profile timer clock            |
| 28   | SIGWINCH          | 忽略     | 窗口尺寸调整                   |
| 29   | SIGIO/SIGPOLL     | 终止     | I/O可用                        |
| 30   | SIGPWR            | 终止     | 电源异常                       |
| 31   | SIGSYS／SYSUNUSED | dump     | 系统调用异常                   |

在不同系统中同一数值可能会代表不同的信号，因此，最好使用信号名而不是信号值。

信号的数值越小，则优先级越高。当进程收到多个待处理信号时，总是先处理优先级别高的信号。

* [iOS 崩溃 crash 大解析·参考 1](https://toutiao.io/posts/443hus/preview)
* [iOS中的Crash探究·参考 2](https://www.bitnpc.com/2018/11/28/iOS%E7%9A%84Crash%E6%8E%A2%E7%A9%B6/)
