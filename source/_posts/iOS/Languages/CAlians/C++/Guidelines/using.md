---
title: C++ using
date: 2021-08-28 14:18:00
tags:
---

## using 用法

```c++
#include <iostream>

using namespace std;    // 用法1

class ClassOne 
{
public:
 int w;
protected:
 int a;
};

class ClassTwo
{
public:
 using ModuleType = ClassOne;   // 用法2
};

template <typename ClassType>class ClassThree : private ClassType
{
public:
 using typename ClassType::ModuleType;    // 用法3
 ModuleType m;
 ClassThree() = default;
 virtual ~ClassThree() = default;
};

void main()
{
 ClassThree<ClassTwo>::ModuleType a;
}
```

在上面代码中，一共有三处使用了 using，它们的作用为：

* 用法1: 引入命名空间
* 用法2: 指定别名
* 用法3: 在子类中引用基类的成员
