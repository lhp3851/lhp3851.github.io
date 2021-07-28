---
title: iOS之RunLoop
abbrlink: 18a887dd
date: 2021-04-20 21:36:02
tags:
---


## 1. [深入理解RunLoop](https://blog.ibireme.com/2015/05/18/runloop/)

### 1.1 Source0、与 Source1

1. Source1 :基于mach_Port的,来自系统内核或者其他进程或线程的事件，可以主动唤醒休眠中的RunLoop（iOS里进程间通信开发过程中我们一般不主动使用）。mach_port大家就理解成进程间相互发送消息的一种机制就好, 比如屏幕点击, 网络数据的传输都会触发sourse1。

2. Source0 ：非基于Port的 处理事件，什么叫非基于Port的呢？就是说你这个消息不是其他进程或者内核直接发送给你的。一般是APP内部的事件, 比如hitTest:withEvent的处理, performSelectors的事件。

**用例：** 一个APP在前台静止着，此时，用户用手指点击了一下APP界面，那么过程就是下面这样的：

我们触摸屏幕,先摸到硬件(屏幕)，屏幕表面的事件会被IOKit先包装成Event,通过mach_Port传给正在活跃的APP , Event先告诉source1（mach_port）,source1唤醒RunLoop, 然后将事件Event分发给source0,然后由source0来处理。

如果没有事件,也没有timer,则runloop就会睡眠, 如果有,则runloop就会被唤醒,然后跑一圈。
