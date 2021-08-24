---
title: React-Native与原生端通信
date: 2021-08-24 10:17:02
tags:
---

## 1. RN 调用原生方法（iOS）[^参考]

```objective-c
//
//  RNBridge.h
//  demo
//
//  Created by chj on 2019/3/20.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>


@interface RNBridge : NSObject<RCTBridgeModule>

@end
```

```objective-c
//
//  RNBridge.m
//  demo
//
//  Created by chj on 2019/3/20.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import "RNBridge.h"
#import <React/RCTBridge.h>

#import "PageAViewController.h"
#import "AppDelegate.h"

@implementation RNBridge
@synthesize bridge = _bridge;

RCT_EXPORT_MODULE();

// RN 跳转原生
RCT_EXPORT_METHOD(jumpNativePage){
  
  dispatch_async(dispatch_get_main_queue(), ^{
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    
    [appDelegate.navigationVCtrl pushViewController:[PageAViewController new] animated:YES];
    
  });
  
}

//
RCT_EXPORT_METHOD(back){
  dispatch_async(dispatch_get_main_queue(), ^{
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    
    [appDelegate.navigationVCtrl popViewControllerAnimated:YES];
    
  });
}


@end
```

```javascript
/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {Component} from 'react';
import {
    NativeModules,
} from 'react-native';

const RNBridge = NativeModules.RNBridge;

<TouchableOpacity style={styles.container}
                onPress={()=>{
                      RNBridge.jumpNativePage()
                    }}>
            </TouchableOpacity>
```

## 2. 原生（iOS）调用RN方法

```objective-c
//
//  SendEventManager.h
//  demo
//
//  Created by chj on 2019/3/20.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>

NS_ASSUME_NONNULL_BEGIN

@interface SendEventManager :  RCTEventEmitter <RCTBridgeModule>
+ (void)emitEventWithName:(NSString *)name andInfo:(NSDictionary *)info;

@end

NS_ASSUME_NONNULL_END
```

```objective-c
//
//  SendEventManager.m
//  demo
//
//  Created by chj on 2019/3/20.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import "SendEventManager.h"

@implementation SendEventManager

RCT_EXPORT_MODULE();

- (NSArray<NSString *> *)supportedEvents
{
  return @[@"ABC"];
}


- (void)startObserving {
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(emitEvent:) name:@"sendEmmit" object:nil];
  
}
- (void)stopObserving {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
  
}
- (void)emitEvent:(NSNotification *)notification{
  [self sendEventWithName:@"ABC" body:notification.userInfo];
  
}
+ (void)emitEventWithName:(NSString *)name andInfo:(NSDictionary *)info{
  [[NSNotificationCenter defaultCenter] postNotificationName:@"sendEmmit"                                                      object:self userInfo:info];
  
}



@end
```

原生使用

```objective-c
[SendEventManager emitEventWithName:@"ABC" andInfo:@{}];
```

RN使用

```javascript
/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {Component} from 'react';
import {
    NativeModules,
    NativeEventEmitter
} from 'react-native';

const sendEventManagerEmitter = new NativeEventEmitter(NativeModules.SendEventManager);

 // 原生给RN发送消息
this.listener = sendEventManagerEmitter.addListener('ABC', (obj)=>{
...
})
componentWillUnmount() {
    this.listener.remove()
}
```

[^参考]: [RN 调用原生方法（iOS）、原生（iOS）调用RN方法](https://www.jianshu.com/p/62da57116689)
