---
title: a-shell
abbrlink: 8786
date: 2021-08-10 14:40:02
tags:
---

在 iOS 设备上提供类 Unix 终端命令的工具。

## 1. 命令

```shell
## 打开新窗口
newWindow
## 关闭当前窗口
exit
## 列举所有可用命令
help -l
```

## 2. 主目录

默认有权限的目录：

`~/Documents/`, `~/Library/` and `~/tmp`

### 2.1 访问 APP 目录

```shell
pickFolder
```

### 2.2 沙盒&书签

```shell
## 给当前目录加书签
bookmark
## 列举所有书签
showmarks
## 跳转到书签
jump mark
## 重命名书签
renamemark
## 删除书签
deletemark
```

## 3. 快捷方式

`Execute Command` 顺序执行命令集合，可以是命令文件，或者命令文本 node

`Put File` and `Get File` 用来收发文件

快捷方式有两种执行方式：APP 拓展（推荐）里 或者 APP 里

`open shortcuts://` 从打开的命令中返回

## 4. 更多

a-shell 安装了： `Python, Lua, JS, C, C++ and TeX.` 这些环境。

### 4.1 C++

编译：`clang program.c`

汇编：`wasm a.out`

链接：`ar`

[可使用工具](https://github.com/holzschu/a-Shell-commands)：`zip, unzip, xz, ffmpeg`

### 4.2 Python

`pip install packagename`

### 4.3 TeX

这个默认没安装，输入任意 TeX 命令，将会提示安装 TeX。LuaTeX 也是一样的。
