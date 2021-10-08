---
title: iOS之持久化
abbrlink: 396dcc83
date: 2021-04-20 21:36:02
tags:
---
## 1. 数据库

### 1.1 [SQLite](https://www.w3cschool.cn/sqlite/sqlite-tutorial.html)

## 1.2 [Core data](https://developer.aliyun.com/article/117778)

### 1.3 [FFMDB](https://github.com/ccgus/fmdb)

#### 1.3.1 [sqlite之WAL模式](https://www.cnblogs.com/huahuahu/p/sqlite-zhiWAL-mo-shi.html)

WAL模式原理

回滚日志的方法是把为改变的数据库文件内容写入日志里，然后把改变后的内容直接写到数据库文件中去。在系统crash或掉电的情况下，日志里的内容被重新写入数据库文件中。日志文件被删除，标志commit着一次commit的结束。

WAL模式于此此相反。原始为改变的数据库内容在数据库文件中，对数据库文件的修改被追加到单独的WAL文件中。当一条记录被追加到WAL文件后，标志着一次commit的结束。因此一次commit不必对数据库文件进行操作，当正在进行写操作时，可以同时进行读操作。多个事务的内容可以追加到一个WAL文件的末尾。

##### 1.3.1.1 `checkpoint`

最后WAL文件的内容必须更新到数据库文件中。把WAL文件的内容更新到数据库文件的过程叫做一次checkpoint。
回滚日志的方法有两种操作：读和写。WAL有三种操作，读、写和`checkpoint`。
默认的，SQL会在WAL文件达到1000page时进行一次 `checkpoint`。进行WAL的时机也可以由应用程序自己决定。

##### 1.3.1.2 并发性

当一个读操作发生在WAL模式的数据库上时，会首先找到WAL文件中最后一次提交，叫做`"end mark"`。每一个事务可以有自己的`"end point"`，但对于一个给定额事务来说，`end mark`是固定的。
当读取数据库中的`page`时，SQLite会先从WAL文件中寻找有没有对应的`page`，从找出离`end mark`最近的那一条记录；如果找不到，那么就从数据库文件中寻找对一个的`page`。为了避免每次事务都要扫描一遍WAL文件，SQLite在共享内存中维护了一个`"wal-index"`的数据结构，帮助快速定位`page`。
写数据库只是把新内容加到WAL文件的末尾，和读操作没有关系。由于只有一个WAL文件，因此同时只能有一个写操作。
`checkpoint`操作可以和读操作并行。但是如果`checkpoint`把一个`page`写入数据库文件，而且这个`page`超过了当前读操作的`end mark`时，`checkpoint`必须停止。否则会把当前正在读的部分覆盖掉。下次`checkpoint`时，会从这个`page`开始往数据库中拷贝数据。
当写操作时，会检查WAL文件被拷贝到数据库的进度。如果已经完全被拷贝到数据库文件中，已经同步，并且没有读操作在使用WAL文件，那么会把WAL文件清空，从其实开始追加数据。保证WAL文件不会无限制增长。

##### 1.3.1.3. 性能

写操作是很快的，因为只需要进行一次写操作，并且是顺序的（不是随机的，每次都写到末尾）。而且，把数据刷到磁盘上是不必须的。（如果`PRAGMA synchronous`是FULL，每次commit要刷一次，否则不刷。）
读操作的性能有所下降，因为需要从WAL文件中查找内容，花费的时间和WAL文件的大小有关。`wal-index`可以缩短这个时间，但是也不能完全避免。因此需要保证WAL文件的不会太大。
为了保护数据库不被损坏，需要在把WAL文件写入数据库之前把WAL文件刷入磁盘；在重置WAL文件之前要把数据库内容刷入数据库文件。此外`checkpoint`需要查找操作。这些因素使得`checkpoint`比写操作慢一些。
默认策略是很多线程可以增长WAL文件。把WAL文件大小变得比1000page大的那个线程要负责进行`checkpoint`。会导致绝大部分读写操作都是很快的，随机有一个写操作非常慢。也可以禁用自动`checkpoint`的策略，定期在一个线程或进程中进行`checkpoint`操作。
高效的写操作希望WAL文件越大越好；高效的读操作希望WAL文件越小越好。两者存在一个`tradeoff`。

## 2. 文件

### 2.1 [浅谈Linux虚拟文件系统](https://zhuanlan.zhihu.com/p/69289429)

## 3. plist

## 4. 归档

## 5. keychain

## 6. Userdefault

### 6.1 [MMKV](https://github.com/Tencent/MMKV/blob/master/README_CN.md)
