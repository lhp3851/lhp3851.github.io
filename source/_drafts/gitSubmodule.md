---
title: Git Submodule
tags:
---

[TOC]

## 1. [Git中submodule](https://zhuanlan.zhihu.com/p/87053283)

### 1.1 创建 submodule

### 1.2 拉取 submodule

### 1.3 submodule 更新

submodule 更新分三种情形

1. submodule 文件夹内的内容发生了未跟踪的内容变动；

2. submodule 文件夹内的内容发生了版本变化；

3. submodule 文件夹内的内容没变，远程有更新；

### 1.4 删除 submodule

网上流传了一些偏法，主要步骤是直接移除模块，并手动修改 ```.gitmodules```、```.git/config``` 和 ```.git/modules``` 内容。包含了一大堆类似```git rm --cached <sub-module>```、```rm -rf <sub-moduel>```、```rm .gitmodules``` 和 ```git rm --cached``` 之类的代码。

实际上这是一种比较野的做法，不建议使用。

根据官方文档的说明，应该使用 ```git submodule deinit``` 命令卸载一个子模块。这个命令如果添加上参数 ```--force```，则子模块工作区内即使有本地的修改，也会被移除。

```shell
git submodule deinit project-sub-1
git rm project-sub-1
```

执行 ```git submodule deinit project-sub-1``` 命令的实际效果，是自动在 ```.git/config``` 中删除了以下内容：

```shell
[submodule "project-sub-1"]
url = <https://github.com/username/project-sub-1.git>
```

执行 git rm project-sub-1 的效果，是移除了 project-sub-1 文件夹，并自动在 .gitmodules 中删除了以下内容：

[submodule "project-sub-1"]
path = project-sub-1
url = <https://github.com/username/project-sub-1.git>
此时，主项目中关于子模块的信息基本已经删除（虽然貌似 .git/modules 目录下还有残余）：

project-main git:(master) ✗ gs
位于分支 master
您的分支与上游分支 'origin/master' 一致。
要提交的变更：
（使用 "git reset HEAD <文件>..." 以取消暂存）
修改： .gitmodules
删除： project-sub-1

可以提交代码：

git commit -m "delete submodule project-sub-1"
至此完成对子模块的删除。
