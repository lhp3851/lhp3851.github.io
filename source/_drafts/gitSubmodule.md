---
title: Git Submodule
tags:
---

[TOC]

## 1. [Git中submodule](https://zhuanlan.zhihu.com/p/87053283)

### 1.1 创建 submodule

在主项目根目录

```shell
git submodule add <submodule_url>
```

### 1.2 拉取 submodule

```shell
cd /path/to/submodule
git clone https://github.com/username/project-main.git --recurse-submodules
```

或者，在主项目根目录下

```shell
git submodule init
git submodule update
```

### 1.3 submodule 更新

对于子模块而言，并不需要知道引用自己的主项目的存在。对于自身来讲，子模块就是一个完整的 Git 仓库，按照正常的 Git 代码管理规范操作即可。

submodule 更新分三种情形。

#### 1.3.1 submodule 文件夹内的内容发生了未跟踪的内容变动

进入 submodule 文件夹，按照子模块内部的版本控制体系提交代码。当提交完成后，主项目的状态则进入了情况2，即当前项目下子模块文件夹内的内容发生了版本变化。

#### 1.3.2. submodule 文件夹内的内容发生了版本变化

在主项目中使用 git status 查看仓库状态时，会显示子模块有新的提交。在这种情况下，可以使用 git add/commit 将其添加到主项目的代码提交中。

#### 1.3.3. submodule 文件夹内的内容没变，远程有更新

通常来讲，主项目与子模块的开发不会恰好是同时进行的。通常是子模块负责维护自己的版本升级后，推送到远程仓库，并告知主项目可以更新对子模块的版本依赖。

在这种情况下，主项目是比较茫然的。

之前曾经提到，主项目可以使用 ```git submodule update``` 更新子模块的代码，但那是指 ```当前主项目文件夹下的子模块目录内容``` 与 ```当前主项目记录的子模块版本``` 不一致时，会参考后者进行更新。

但如今这种情况下，后者 ```当前主项目记录的子模块版本``` 还没有变化，在主项目看来当前情况一切正常。

此时，需要让主项目主动进入子模块拉取新版代码，进行升级操作。

通常流程是：

```shell
cd /path/to/submodule
git pull origin master
```

子模块目录下的代码版本会发生变化，转到情况2的流程进行主项目的提交。

当主项目的子项目特别多时，可能会不太方便，此时可以使用 git submodule 的一个命令 foreach 执行：

```shell
git submodule foreach 'git pull origin master'
```

### 1.4 删除 submodule

网上流传了一些偏法，主要步骤是直接移除模块，并手动修改 ```.gitmodules```、```.git/config``` 和 ```.git/modules``` 内容。包含了一大堆类似```git rm --cached <sub-module>```、```rm -rf <sub-moduel>```、```rm .gitmodules``` 和 ```git rm --cached``` 之类的代码。

实际上这是一种比较野的做法，不建议使用。

根据官方文档的说明，应该使用 ```git submodule deinit``` 命令卸载一个子模块。这个命令如果添加上参数 ```--force```，则子模块工作区内即使有本地的修改，也会被移除。

```shell
git submodule deinit project-sub

git rm project-sub
```

执行 ```git submodule deinit project-sub``` 命令的实际效果，是自动在 ```.git/config``` 中删除了以下内容：

```shell
[submodule "project-sub"]

url = <https://github.com/username/project-sub.git>
```

执行 ```git rm project-sub``` 的效果，是移除了 ```project-sub``` 文件夹，并自动在 ```.gitmodules``` 中删除了以下内容：

```shell
[submodule "project-sub"]

path = /path/to/submodule

url = <https://github.com/username/project-sub.git>
```

此时，主项目中关于子模块的信息基本已经删除（虽然貌似 .git/modules 目录下还有残余）：

```shell
project-main git:(master) ✗ gs
位于分支 master
您的分支与上游分支 'origin/master' 一致。
要提交的变更：
（使用 "git reset HEAD <文件>..." 以取消暂存）
修改： .gitmodules
删除： project-sub
````

可以提交代码：

```shell
git commit -m "delete submodule project-sub"
```

至此完成对子模块的删除。
