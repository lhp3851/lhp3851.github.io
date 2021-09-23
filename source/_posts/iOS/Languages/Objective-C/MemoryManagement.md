---
title: iOS之内存管理
abbrlink: 34950
date: 2021-09-16 22:16:00
tags:
---

## 1. 基础

objc4 源码 与 [基本类型](./Types.md)

## 2 对象初始化

```objective-c
Car *car = [[Car alloc] init];
// or
Car *car = [Car new];
```

* `alloc`: 计算/分配内存、关联 `isa`
* `init` 返回 `self`
* `new` 相当于 先调用 `alloc` 在调用 `init`

## 3 内存模型

```Objective-C
struct objc_class {
    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;

#if !__OBJC2__
    Class _Nullable super_class                              OBJC2_UNAVAILABLE;
    const char * _Nonnull name                               OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list * _Nullable ivars                  OBJC2_UNAVAILABLE;
    struct objc_method_list * _Nullable * _Nullable methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache * _Nonnull cache                       OBJC2_UNAVAILABLE;
    struct objc_protocol_list * _Nullable protocols          OBJC2_UNAVAILABLE;
#endif

} OBJC2_UNAVAILABLE;
/* Use `Class` instead of `struct objc_class *` */

/// An opaque type that represents an Objective-C class.
typedef struct objc_class *Class;
```

```Objective-C
@interface NSObject <NSObject> {
    Class isa  OBJC_ISA_AVAILABILITY;
}
```

对象获取类 isa

```Objective-C
- (Class)class {
    return object_getClass(self);
}

Class object_getClass(id obj)
{
    if (obj) return obj->getIsa();
    else return Nil;
}

inline Class 
objc_object::getIsa() 
{
    if (isTaggedPointer()) {
        uintptr_t slot = ((uintptr_t)this >> TAG_SLOT_SHIFT) & TAG_SLOT_MASK;
        return objc_tag_classes[slot];
    }
    return ISA();
}

inline Class 
objc_object::ISA() 
{
    assert(!isTaggedPointer()); 
    return (Class)(isa.bits & ISA_MASK);
}
```

OC 有一个类似的方法，不过这个方法是通过名字获取相应的类

```Objective-C
static Class getClass(const char *name)
{
    runtimeLock.assertLocked();

    // Try name as-is
    Class result = getClass_impl(name);
    if (result) return result;

    // Try Swift-mangled equivalent of the given name.
    if (char *swName = copySwiftV1MangledName(name)) {
        result = getClass_impl(swName);
        free(swName);
        return result;
    }

    return nil;
}
```

![oc 内存模型](../Resources/oc_memory_struct.webp)

获取 isa

* [iOS底层原理总结 - 探寻OC对象的本质](https://juejin.cn/post/6844903588150378509)

## 4 内存管理

### 4.1 内存管理原则

* 自己生成的对象，自己持有
* 非自己生成的对象，自己也能持有
* 不再需要自己持有的对象，要释放
* 非自己持有的对象，无法释放

| 对象操作         | OC 方法                           |
| :--------------- | :-------------------------------- |
| 生成并持有的对象 | alloc/new/copy/mutableCopy 等方法 |
| 持有对象         | retain                            |
| 释放对象         | release                           |
| 废弃对象         | dealloc                           |

### 4.2 内存管理方式

#### 4.2.1 autorelease pool

#### 4.2.2 所有权修饰符

__strong

__weak

__unsafe_unretain

__autorelease

#### 4.2.3 属性权限修饰符

copy

assign

strong

循环引用&内存泄漏&Weak 原理

[weak 实现原理](https://www.jianshu.com/p/13c4fb1cedea)

Block 内存管理

野指针、悬垂指针（腾讯方案）

僵尸代码

## 5. 内存泄漏

### 5.1 [iOS 内存泄漏场景与解决方案](https://juejin.cn/post/6844904070344343565#heading-10)
