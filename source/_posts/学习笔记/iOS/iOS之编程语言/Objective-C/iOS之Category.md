---
title: iOS之Category
date: 2021-05-22
tags:  
---

## 1. [深入理解Objective-C：Category](https://tech.meituan.com/2015/03/03/diveintocategory.html)

## 2. [iOS中Category的底层实现原理](https://juejin.cn/post/6844904039671398407)

```objective-c
_objc_init: 
dyld_register_image_state_change_handler(dyld_image_state_bound,1, &map_images);

_read_images: 
addUnattachedCategoryForClass(cat, cls, hi)
remethodizeClass(cls)   

attachCategoryMethods(cls, cats, &vtableAffected) 

attachMethodLists(cls, mlists, mcount, NO, fromBundle, inoutVtablesAffected) 
```
