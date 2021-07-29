---
title: iOS之 Xcode Build 自动化
abbrlink: a857ced4
date: 2021-04-20 21:36:02
tags:
---

## 1. 自动化命令配置项

1. Project name: Bookshop.xcodeproj
2. Workspace name: Bookshop.workspace
3. Build Configurations: Debug and Release
4. Targets: bookshop_dev and bookshop_release
5. Schemes: bookshop_dev_scheme and bookshop_appStore_scheme.

* The Build, Run, Test and Analyze are using Debug configuration.
* The Profile and Archive are using Release configuration. Each of the scheme only includes 1 related target.

## 2. Xcode build

### 2.1 显示项目信息--list

```shell
xcodebuild -list

Information about project "_Pods":
    Targets:
        Pods-Bookshop_Example
        Pods-Bookshop_Tests
        Bookshop

    Build Configurations:
        Debug
        Release

    If no build configuration is specified and -scheme is not passed then "Release" is used.

    Schemes:
        Pods-Bookshop_Example
        Pods-Bookshop_Example
        Pods-Bookshop_Tests
        Pods-Bookshop_Tests
        Bookshop
        Bookshop
```

### 2.2  清理工程--Clean

```shell
xcodebuild clean -workspace Bookshop.xcworkspace -scheme bookshop_dev_scheme
xcodebuild clean -project Bookshop.xcodeproj -scheme bookshop_dev_scheme
```

## 2.3 编译工程--build

```shell
xcodebuild -workspace sm_ios_base.xcworkspace -scheme sm_ios_base-Example -configuration Debug

xcodebuild -project _Pods.xcodeproj -target sm_ios_base  -configuration Debug
```

## 2.4 打包--archive

```shell
xcodebuild archive -workspace Bookshop.xcworkspace -scheme bookshop_dev_scheme -archivePath ~/Downloads/bookshop_dev.xcarchive
```

## 2.5 导出 IPA

```shell
xcodebuild -exportArchive -archivePath ~/Downloads/bookshop_dev.scarchive -exportPath ~/Downloads -exportOptionsPlist ~/Downloads/ExportOptions.plist
```

### 2.5.1  ExportOptions.plist

这个文件允许在打IPA包的时候，指定一些配置选项。一般在Xcode 打包的时候，有个 Addtional Option 下面可以勾选这个选项，勾选后，导出的包里面就有这个文件。

自动签名类型的 ExportOptions.plist：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>compileBitcode</key>
  <true/>
  <key>method</key>
  <string>ad-hoc</string>
  <key>signingStyle</key>
  <string>automatic</string>
  <key>stripSwiftSymbols</key>
  <true/>
  <key>teamID</key>
  <string>YourTeamID</string>
  <key>thinning</key>
  <string>&lt;none&gt;</string>
</dict>
</plist>
```

手动签名的 ExportOptions.plist：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
 <key>compileBitcode</key>
 <true/>
 <key>method</key>
 <string>ad-hoc</string>
 <key>provisioningProfiles</key>
 <dict>
 <key>AppBundleID</key>
 <string>AppProvisioningProfileNameInAppleDeveloperAccount</string>
 <key>AppBundleID.NotificationServiceExtension</key>
 <string>AppBundleID</string>
 </dict>
 <key>signingCertificate</key>
 <string>iPhone Distribution</string>
 <key>signingStyle</key>
 <string>manual</string>
 <key>stripSwiftSymbols</key>
 <true/>
 <key>teamID</key>
 <string>YourTeamID</string>
 <key>thinning</key>
 <string>&lt;none&gt;</string>
</dict>
</plist>
```

## 3. 一个打包脚本

### 3.1 显示项目信息

```shell
xcodebuild -list
```

### 3.2 打包

```shell
xcodebuild clean -workspace SUMusic.xcworkspace -scheme SUMusic

xcodebuild build -workspace SUMusic.xcworkspace -scheme SUMusic

xcodebuild archive -workspace SUMusic.xcworkspace -scheme SUMusic -archivePath ~/Desktop/Packages/SUMusic/SUMusic.xcarchive

xcodebuild -exportArchive -archivePath ~/Desktop/Packages/SUMusic/SUMusic.xcarchive -exportPath ~/Desktop/Packages/SUMusic/ -exportOptionsPlist ~/Desktop/Packages/SUMusic/ExportOptions.plist -allowProvisioningUpdates
```
