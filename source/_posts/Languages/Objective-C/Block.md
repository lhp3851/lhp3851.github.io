---
title: Block
abbrlink: 42dab826
date: 2021-04-20 00:00:00
tags:
---

## 1. [iOS-Block底层实现原理](https://limeng99.club/learning/2020/05/25/iOS-Block底层实现原理.html)

## 2. Block 类型

### 2.1 全局 Block

```c
void (^global_block)(void) = ^{
    NSLog(@"global_block");
};
```

### 2.2 栈 Block

```c
 __block int age = 1;
void (^stack_block)(void) = ^{
    NSLog(@"stack_block %d", age++);
};
```

### 2.3 堆 Block

```c
void (^malloc_block)(void) = [stack_block copy];
```

block 发生 copy 的时机：

1. copy 操作；
2. 函数返回值；
3. 赋值给__strong 修饰符 id 类型的类 或者 Block 类型成员时；
4. 方法名中有 useingBlock 的 cocoa 框架方法或者 GCD 中的 api 传递时；

## 3. Block 内部结构

1. 全局变量捕获，不影响 block 结构；
2. auto 变量 捕获成 block 结构体内的普通变量；
3. static 变量捕获成 block 结构体内的指针类型变量；
4. 对象型变量捕获成 block 结构体内的对象型变量；
5. `__block` 型捕获成引用型 block 结构体；
6. `__weak` 型捕获成对象型 `__weak` block 结构体；

### 3.1 普通 Block 结构

```c
struct __block_impl {
  void *isa;      //isa指针，所以说Block是对象
  int Flags;
  int Reserved;
  void *FuncPtr;  //函数指针
};

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  int age;
  // 构造函数（类似于OC的init方法），返回结构体对象
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int _age, int flags=0) : age(_age) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

static void __main_block_func_0(struct __main_block_impl_0 *__cself) {
  int age = __cself->age; // bound by copy
  NSLog((NSString *)&__NSConstantStringImpl__var_folders_sx_ygl_c8ln07jdwrz6w5rgbq8m0000gn_T_blcok_8142ea_mi_0, age);
}

static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0)};
```

### 3.2 捕获引用型变量 Block 结构

```c
struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  LMPerson *person;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, LMPerson *_person, int flags=0) : person(_person) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};
```

### 3.3 捕获Weak型变量 Block 结构

```c
// cannot create __weak reference because the current deployment target does not support weak references 报错时使用一下命令
// xcrun -sdk iphoneos clang -arch arm64 -rewrite-objc -fobjc-arc -fobjc-runtime=ios-8.0.0 main.m

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  LMPerson *__weak weakPerson;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, LMPerson *__weak _weakPerson, int flags=0) : weakPerson(_weakPerson) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
  // copy函数
  void (*copy)(struct __main_block_impl_0*, struct __main_block_impl_0*);
  // dispose函数
  void (*dispose)(struct __main_block_impl_0*);
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0), __main_block_copy_0, __main_block_dispose_0};

//copy函数内部会调用_Block_object_assign函数
static void __main_block_copy_0(struct __main_block_impl_0*dst, struct __main_block_impl_0*src) {_Block_object_assign((void*)&dst->weakPerson, (void*)src->weakPerson, 3/*BLOCK_FIELD_IS_OBJECT*/);}

// dispose函数内部会调用_Block_object_dispose函数
static void __main_block_dispose_0(struct __main_block_impl_0*src) {_Block_object_dispose((void*)src->weakPerson, 3/*BLOCK_FIELD_IS_OBJECT*/);}
```

### 3.4 捕获 __block 型变量 Block 结构

```c
// main.cpp
struct __Block_byref_age_0 {
  void *__isa;
  __Block_byref_age_0 *__forwarding; // 指向自身的指针
  int __flags;
  int __size;
  int age; // 使用值
};

struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  __Block_byref_age_0 *age; // by ref
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, __Block_byref_age_0 *_age, int flags=0) : age(_age->__forwarding) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

static void __main_block_func_0(struct __main_block_impl_0 *__cself) {
  __Block_byref_age_0 *age = __cself->age; // bound by ref
      // __forwarding指向的结构体的age改为30，也就是__Block_byref_age_0结构体age本身的age的值修改为30
      (age->__forwarding->age) = 30;
      // 通过__forwarding找到指针，然后去取出age值。
      NSLog((NSString *)&__NSConstantStringImpl__var_folders_sx_ygl_c8ln07jdwrz6w5rgbq8m0000gn_T_main_5da7ea_mi_0, (age->__forwarding->age));
  }
```

## 4 循环引用处理

1. weak
2. __block
3. __unsafe_unretained

## 5. Block 的变量捕获原理

### 5.1 [你真的理解__block修饰符的原理么？](https://blog.csdn.net/abc649395594/article/details/47086751)

参考[^深入理解iOS的block]
[^深入理解iOS的block]: [深入理解iOS的block](https://juejin.cn/post/6844903893176958983#heading-37)
