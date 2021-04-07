# iOS 自动化

## 1. 模拟器

### 1.1 模拟器列表

```shell
instruments -s

// or 

xcrun xctrace --list devices
```

### 1.2 启动模拟器

```shell
xcrun instruments -w 'iPhone X'

// or

open -a Simulator
```

## 2. 模拟器应用

### 2.1 安装 App

```xcrun simctl install booted /Users/builder/builder/document/other/551/Payload/DYZB.app```

### 2.2 启动 App

```xcrun simctl launch booted 'com.tencent.live4iphone'```

### 2.3 卸载 App

```xcrun simctl uninstall booted 'com.tencent.live4iphone'```

## 3. 附注

另外一套工具 idevice[^idevice].

[^idevice]: [idevice](https://github.com/libimobiledevice/libimobiledevice)
