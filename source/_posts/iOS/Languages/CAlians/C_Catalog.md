---
title: 系统中断信号
abbrlink: f317f6e0
date: 2021-04-20 00:00:00
tags:
---

```shell
# 查看信号列表
kill -l

Constant    Explanation
SIGTERM    termination request, sent to the program
SIGSEGV    invalid memory access (segmentation fault)
SIGINT    external interrupt, usually initiated by the user
SIGILL    invalid program image, such as invalid instruction
SIGABRT    abnormal termination condition, as is e.g. initiated by abort()
SIGFPE       erroneous arithmetic operation such as divide by zero
```
