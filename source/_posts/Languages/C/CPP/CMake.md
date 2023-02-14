---
title: 编译工具 CMake 入门
abbrlink: 56914
date: 2021-09-01 10:56:00
tags:
---

[TOC]

cmake 的用法，分为三步

1. 编写 CMake 配置文件 CMakeLists.txt 。
2. 执行命令 `cmake PATH` 或者 `ccmake PATH` 生成 Makefile。其中， PATH 是   CMakeLists.txt 所在的目录。
3. 使用 `make` 命令进行编译。

`ccmake` 和 `cmake` 的区别在于前者提供了一个交互式的界面。

## 1. 设置项目

### 1.1 设置名称与版本

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# add the executable
add_executable(Tutorial tutorial.cxx)
```

### 1.2 设置 C++ 编译器环境

比如可以这么设置 C++11

```cmake
# specify the C++ standard 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

### 1.3 设置 GDB

CMake 支持 gdb 的设置，也很容易，只需要指定 Debug 模式下开启 -g 选项

```cmake
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
```

## 2. 编译多个目录多个文件

例如工程文件目录如下：

```shell
./Tutorial
    |
    +--- main.cc
    |
    +--- math/
          |
          +--- MathFunctions.cc
          |
          +--- MathFunctions.h

```

首先需要在 Tutorial 文件夹和 math 文件夹下，分别建一个 CMakeLists.txt 文件，其中 Tutorial 目录下的 CMakeLists.txt 称为顶层 CMakeLists.txt。

Tutorial 目录下的 CMakeLists.txt 内容如下

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# 项目信息
project(Tutorial VERSION 1.0)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
# 方法签名为：aux_source_directory(<dir> <variable>)
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(math)

# 指定生成目标 
add_executable(Tutorial main.cc)

# 添加链接库
target_link_libraries(Tutorial MathFunctions)
```

math 目录下的 CMakeLists.txt 内容如下

```cmake
# 查找当前目录下的所有源文件，并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(MathFunctions ${DIR_LIB_SRCS})
```

## 3. 编译选项

### 3.1 设置版本

在 CMakeLists.txt 文件里添加

```cmake
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file(config.h.in config.h)

target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
```

创建 `config.h.in` 配置文件

```cmake
// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

在代码里使用参数选项

```cpp
if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
```

### 3.2 自定义选项

CMake 允许为项目增加编译选项，可以根据用户的环境和需求选择最合适的编译方案。

首先在顶层 CMakeLists.txt 添加选项

```cmake
# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)

# 项目信息
project(Tutorial VERSION 1.0)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
       "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory (math)  
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Tutorial ${DIR_SRCS})
target_link_libraries (Tutorial  ${EXTRA_LIBS})
```

`config.h.in` 文件内容如下

```cmake
#cmakedefine USE_MYMATH
```

代码里，可以这么使用

```cpp
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
  #include "math/MathFunctions.h"
#else
  #include <math.h>
#endif


int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    
#ifdef USE_MYMATH
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);
#else
    printf("Now we use the standard library. \n");
    double result = pow(base, exponent);
#endif
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}
```

然后可以去编译执行一下看看效果，由于这是一个有选项的编译过程，可以用 ccmake 尝试一下。

### 3.3 环境检查

有时候可能要对系统环境做点检查，例如要使用一个平台相关的特性的时候。在这个例子中，我们检查系统是否自带 `pow` 函数。如果带有 `pow` 函数，就使用它；否则使用我们定义的 `power` 函数。

首先在顶层 `CMakeLists` 文件中添加 `CheckFunctionExists.cmake` 宏，并调用 `check_function_exists` 命令测试链接器是否能够在链接阶段找到 `pow` 函数。

```cmake
# 检查系统是否支持 pow 函数
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (pow HAVE_POW)
```

或者使用 `CheckSymbolExists` 的 `check_symbol_exists`检查

```cmake
include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
if(NOT (HAVE_LOG AND HAVE_EXP))
  unset(HAVE_LOG CACHE)
  unset(HAVE_EXP CACHE)
  set(CMAKE_REQUIRED_LIBRARIES "m")
  check_symbol_exists(log "math.h" HAVE_LOG)
  check_symbol_exists(exp "math.h" HAVE_EXP)
  if(HAVE_LOG AND HAVE_EXP)
    target_link_libraries(MathFunctions PRIVATE m)
  endif()
endif()
```

将上面这段代码放在 configure_file 命令前。

接下来修改 `config.h.in` 文件，预定义相关的宏变量。

```cmake
// does the platform provide pow function?
#cmakedefine HAVE_POW
```

最后一步是修改 cpp 源代码 ，在代码中使用宏和函数：

```cpp
#ifdef HAVE_POW
    printf("Now we use the standard library. \n");
    double result = pow(base, exponent);
#else
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);
#endif
```

## 4. 测试

添加测试同样很简单。`CMake` 提供了一个称为 `CTest` 的测试工具。我们要做的只是在项目根目录的 `CMakeLists` 文件中调用一系列的 `add_test` 命令。

```cmake
# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test (test_run Demo 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage Tutorial)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 测试 5 的平方
add_test (test_5_2 Tutorial 5 2)

set_tests_properties (test_5_2
 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 测试 10 的 5 次方
add_test (test_10_5 Tutorial 10 5)

set_tests_properties (test_10_5
 PROPERTIES PASS_REGULAR_EXPRESSION "is 100000")

# 测试 2 的 10 次方
add_test (test_2_10 Tutorial 2 10)

set_tests_properties (test_2_10
 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")
```

其中，第一个测试 test_run 用来测试程序是否成功运行并返回 0 值。 `PASS_REGULAR_EXPRESSION` 用来测试输出是否包含后面跟着的字符串。

上面的代码，可以简洁一点

```cmake
# 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} Tutorial ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# 使用该宏进行一系列的数据测试
do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")
```

**提示：** CTest 文档，可以查看`man 1 ctest`。

## 5. 安装

### 5.1 make 安装

在 `CMakeLists.txt` 指定安装路径与头文件存放路径。对于子目录，比如 math，可以在子目录下的 `CMakeLists.txt`文件添加

```cmake
# 指定 MathFunctions 库的安装路径
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```

然后在顶层 `CMakeLists.txt`文件里添加

```cmake
# 指定安装路径
install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
```

通过上面的定制，生成的 `Tutorial` 文件和 `MathFunctions` 函数库 `libMathFunctions.o` 文件将会被复制到 `/usr/local/bin` 中，而 `MathFunctions.h` 和生成的 `config.h` 文件则会被复制到 `/usr/local/include` 中。我们可以编译然后安装`sudo make install`验证一下（顺带一提的是，这里的 `/usr/local/` 是默认安装到的根目录，可以通过修改 `CMAKE_INSTALL_PREFIX` 变量的值来指定这些文件应该拷贝到哪个根目录）：

### 5.2 生成安装包

如何配置生成各种平台上的安装包，包括二进制安装包和源码安装包。为了完成这个任务，我们需要用到 CPack ，它同样也是由 CMake 提供的一个工具，专门用于打包。

首先在顶层的 CMakeLists.txt 文件尾部添加下面几行：

```cmake
# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)
```

然后编译，并执行 CPack 命令，生成二进制安装包

```cmake
cpack -C CPackConfig.cmake
```

或则生成源码安装包

```cmake
cpack -C CPackSourceConfig.cmake
```

命令执行后，会在该目录下生成安装包，可以通过如下命令安装

```sh
sh Tutorial-1.0.1-Linux.sh
```

此时会出现一个由 CPack 自动生成的交互式安装界面，按照提示操作就好。

然后，就可以通过在终端验证该可执行程序

```sh
./Tutorial-1.0.1-Linux 5 2
```

## 6. 平台迁移

可以将其他工具系列的项目迁移到 cmake 上来，具体参考[迁移到 cmake](https://gitlab.kitware.com/cmake/community/-/wikis/home#converters-from-other-buildsystems-to-cmake)

## 7. 杂项

### 7.1 CMake Language

* 英文版：[CMake Language](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#syntax)
* 中文版：[CMake Language](https://vvingerfly.github.io/2018/04-15-CMakeLanguage/)

### 7.2 [CMake 官方文档](https://cmake.org/cmake/help/v3.21/index.html)

### 7.3 [CMake 社区文档](https://gitlab.kitware.com/cmake/community)

### 7.4 [CMake 入门实战](https://www.hahack.com/codes/cmake/)

### 7.5 [Cmake中文实战教程](https://brightxiaohan.github.io/CMakeTutorial/)

### 7.6 [CMake 支持的变量](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables)

## 8. 本文使用到的资源

main.cpp 源代码

```cpp
#include <stdio.h>
#include <stdlib.h>

/**
 * power - Calculate the power of number.
 * @param base: Base value.
 * @param exponent: Exponent value.
 *
 * @return base raised to the power exponent.
 */
double power(double base, int exponent)
{
    int result = base;
    int i;
    
    if (exponent == 0) {
        return 1;
    }
    
    for(i = 1; i < exponent; ++i){
        result = result * base;
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = power(base, exponent);
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}
```
