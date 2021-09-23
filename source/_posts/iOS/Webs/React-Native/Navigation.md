---
title: React-Native 导航
tags: React-Native Navigation
abbrlink: 5695
date: 2021-08-09 11:06:02
---

## 1. React Navigation

## 2. [React Native Navigation](https://wix.github.io/react-native-navigation/docs/before-you-start)

### 2.1 开始

```shell
yarn add react-native-navigation
```

在 react-native 代码里注册

```git
+import { Navigation } from "react-native-navigation";
-import {AppRegistry} from 'react-native';
import App from "./App";
-import {name as appName} from './app.json';

-AppRegistry.registerComponent(appName, () => App);
+Navigation.registerComponent('com.myApp.WelcomeScreen', () => App);

+Navigation.events().registerAppLaunchedListener(() => {
+   Navigation.setRoot({
+     root: {
+       stack: {
+         children: [
+           {
+             component: {
+               name: 'com.myApp.WelcomeScreen'
+             }
+           }
+         ]
+       }
+     }
+  });
+});
```

在 iOS 代码注册

```objc
#import "AppDelegate.h"

#import <React/RCTBundleURLProvider.h>
#import <React/RCTRootView.h>
#import <ReactNativeNavigation/ReactNativeNavigation.h>

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  [ReactNativeNavigation bootstrapWithDelegate:self launchOptions:launchOptions];

  return YES;
}

- (NSURL *)sourceURLForBridge:(RCTBridge *)bridge
{
  #if DEBUG
    return [[RCTBundleURLProvider sharedSettings] jsBundleURLForBundleRoot:@"index" fallbackResource:nil];
  #else
    return [[NSBundle mainBundle] URLForResource:@"main" withExtension:@"jsbundle"];
  #endif
}

- (NSArray<id<RCTBridgeModule>> *)extraModulesForBridge:(RCTBridge *)bridge {
  return [ReactNativeNavigation extraModulesForBridge:bridge];
}

@end
```

### 2.2 基本用法

#### 2.2.1 设置根页面

```javascript
import React from 'react';
import { View, Text, Button, StyleSheet } from 'react-native';
import { Navigation } from 'react-native-navigation';

const HomeScreen = (props) => {
  return (
    <View style={styles.root}>
      <Text>Home Screen</Text>
    </View>
  );
};

Navigation.registerComponent('Home', () => HomeScreen); // 注册页面，每一个页面都需要注册

Navigation.events().registerAppLaunchedListener(async () => {
  Navigation.setRoot({
    root: {
      stack: {
        children: [
          {
            component: {
              name: 'Home'
            }
          }
        ]
      }
    }
  });
});

const styles = StyleSheet.create({
  root: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: 'whitesmoke'
  }
});
```

#### 2.2.2 页面配置

```javascript
const HomeScreen = (props) => {
  return (
    <View style={styles.root}>
      <Text>Hello React Native Navigation 👋</Text>
    </View>
  );
};
HomeScreen.options = {
  topBar: {
    title: {
      text: 'Home',
      color: 'white'
    },
    background: {
      color: '#4d089a'
    }
  }
}
```

#### 2.2.3 导航配置

```javascript
Navigation.setDefaultOptions({
  statusBar: {
    backgroundColor: '#4d089a'
  },
  topBar: {
    title: {
      color: 'white'
    },
    backButton: {
      color: 'white'
    },
    background: {
      color: '#4d089a'
    }
  }
});
```

#### 2.2.4 导航 push

```javascript
Navigation.push(props.componentId, {
  component: {
    name: 'Settings', // Push the screen registered with the 'Settings' key
    options: { // Optional options object to configure the screen
      topBar: {
        title: {
          text: 'Settings' // Set the TopBar title of the new Screen
        }
      }
    }
  }
});
```

### 2.3 Layout

#### 2.3.1 Stack

##### 2.3.1.1 stack 设置

```javascript
const stack = {
  children: [
    {
      component: {
        name: 'RootComponent',
      },
    },
    {
      component: {
        name: 'SecondComponent',
      },
    },
  ],
};
```

##### 2.3.1.2 设置[更新]导航栏按钮

```javascript
topBar: {
  rightButtons: [
    {
      id: 'SomeUniqueId',
      component: {
        name: 'ButtonComponent',
        passProps: {
          count: 0
        },
      },,
    },
  ];
}

// Update props
Navigation.updateProps('SomeUniqueId', {
  count: 1,
});
```

#### 2.3.2 Bottom Tabs

```javascript
bottomTabs: {
  id: 'BOTTOM_TABS_LAYOUT',
  children: [
    {
      stack: {
        id: 'HOME_TAB',
        children: [
          {
            component: {
              id: 'HOME_SCREEN',
              name: 'HomeScreen'
            }
          }
        ],
        options: {
          bottomTab: {
            icon: require('./home.png')
          }
        }
      }
    },
    {
      stack: {
        id: 'PROFILE_TAB',
        children: [
          {
            component: {
              id: 'PROFILE_SCREEN',
              name: 'ProfileScreen'
            }
          }
        ],
        options: {
          bottomTab: {
            icon: require('./profile.png')
          }
        }
      }
    }
  ]
}
```

#### 2.3.2.1 Tabs 选择

```javascript
Navigation.mergeOptions('BOTTOM_TABS_LAYOUT', {
  bottomTabs: {
    currentTabIndex: 1
  }
});
```

或者

```javascript
Navigation.mergeOptions(this.props.componentId, {
  bottomTabs: {
    currentTabId: this.props.componentId
  }
});
```

#### 2.3.3 Side Menu

```javascript
const React = require('react');
const Navigation = require('react-native-navigation');
const { View, Text } = require('react-native');

class SideMenuCenterScreen extends React.Component {
  static options() {
    return {
      topBar: {
        leftButtons: {
          id: 'sideMenu',
          icon: require('./menuIcon.png')
        }
      }
    };
  }

  constructor(props) {
    super(props);
    Navigation.events().bindComponent(this);
  }

  render() {
    return (
      <View>
        <Text>Click the hamburger icon to open the side menu</Text>
      </View>
    );
  }

  navigationButtonPressed({ buttonId }) {
    if (buttonId === 'sideMenu') {
      Navigation.mergeOptions(this, {
        sideMenu: {
          left: {
            visible: true
          }
        }
      });
    }
  }
}
```

导航

```javascript
Navigation.push('CenterStack', {
  component: {
    name: Screens.Pushed,
    options: {
      sideMenu: {
        center: {
          stack: {
            id: 'CenterStack',
            children: []
          }
        },
        left: {
          visible: false
        }
      }
    }
  }
});
```

#### 2.3.4 原生 ViewController

在 react-native 里可以使用 iOS 的原生 viewcontroller，不过需要在 iOS 端注册

```objc
[ReactNativeNavigation registerExternalComponent:@"MyExternalComponent" callback:^UIViewController *(NSDictionary *props, RCTBridge *bridge) {
    return [[ExternalViewController alloc] initWithProps:props];
}];
```

### 2.4 生命周期

#### 2.4.1 页面生命周期

* `componentDidAppear` - 当页面显示的时候调用
* `componentDidDisappear` - 当页面隐藏或者消失的时候调用

* `componentDidMount` - 组件第一次关联到渲染树的时候调用一次
* `componentWillUnmount` - 当组件销毁的时候调用一次

#### 2.4.2 页面创建

当组件第一次创建并挂载的时候，按顺序调用一下生命周期函数

* constructor()
* render()
* componentDidMount()
* componentDidAppear()

#### 2.4.3 页面消失

* componentDidDisappear()
* componentWillUnmount()

#### 2.4.4 Modal & Overlay

##### 2.4.4.1 Modal

当页面显示时， Modals 样式为 `pageSheet` 或者 `overCurrentContext` , 先前的内容依然可见. 所以 `componentDidDisappear` 事件不会触发. 当页面消失时，反之依然，`componentDidAppear` 也不会触发。

##### 2.4.4.2 Overlay

* constructor()
* render()
* componentDidMount()
* componentDidAppear()

### 2.5 导航传参

```javascript
Navigation.push(this.props.componentId, {
  component: {
    name: 'UserProfile',
    id: 'PROFILE_SCREEN_ID'
    passProps: {
      name: 'John Doe',
      status: 'online'
    }
  }
});
```

其中 passProps 不会被序列化。
