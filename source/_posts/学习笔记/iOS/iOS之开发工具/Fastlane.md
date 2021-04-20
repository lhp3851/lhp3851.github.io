---
title: Fastlane 指南
date: 2021-04-20 21:36:02
tags:  
---

[TOC]

## 1. [Fastlane](https://docs.fastlane.tools/)

fastlane 是一个移动端用来做自动化部署的工具。他可以用来做一些反复枯燥无味的工作，比如截图，代码签名，APP 发版。

## 2. 环境配置

### 2.1 Bundler

在 fastlane 中推荐使用 Bundler 和 Gemfile 管理依赖。

* 安装 Bundler

```shell
gem install bundler
```

* 在项目根目录创建 Gemfile 文件，这个文件是管理 fastlane 的依赖，并把文件加入 git 管理，文件内容如下

```ruby
source "https://rubygems.org"

gem "fastlane"
```

* 运行 fastlane 依赖更新

```shell
bundle update
```

* fastlane 使用
  
```shell
bundle exec fastlane [lane]
```

* 安装 fastlane 依赖
  
```shell
bundle install
```

* 更新 fastlane
  
```shell
bundle update fastlane
```

### 2.2 设置 fastlane

#### 2.2.1 fastlane 初始化

默认使用 ruby 分支

```shell
fastlane init
```

可以指定使用 swift 分支（这个分支正式版还没有发布）

```shell
fastlane init swift
```

初始化的过程中会有一些问题需要回答，根据项目偏好，如实回答就好。

初始化玩之后，项目根目录下面会生成一个 fastlane 文件夹，里面的内容，感兴趣的话，可以都看下，基本上都是一些自动打包过程中需要使用的信息，有些信息是初始化过程中一些问题的答案，有些事根据提供的 AppleID，fastlane 用 Apple Store Connect API 从你的开发者账号中拉取下来的。

#### 2.2.2 注意

* shell 环境配置最好加上这两句，避免一些编码问题导致配置不兼容的情况
  
```shell
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
```

## 3. 运行测试用例

### 3.1 使用

运行单元测试或者 UI 测试的话，可以在 fastfile 中加入 lane

```ruby
lane :tests do
  run_tests(scheme: "MyAppTests")
end
```

或者

```ruby
lane :tests do
  run_tests(workspace: "Example.xcworkspace",
            devices: ["iPhone 6s", "iPad Air"],
            scheme: "MyAppTests")
end
```

然后在终端的项目根目录下，运行

```shell
fastlane tests
```

## 4. [截图](https://docs.fastlane.tools/getting-started/ios/screenshots/)

## 5. [Beta 部署](https://docs.fastlane.tools/getting-started/ios/beta-deployment/)

### 5.1 项目编译

```ruby
lane :beta do
  build_app(scheme: "MyApp")
end
```

或者

```ruby
lane :beta do
  build_app(scheme: "MyApp",
            workspace: "Example.xcworkspace",
            include_bitcode: true)
end
```

然后在终端的项目根目录下，运行

```shell
fastlane beta
```

### 5.2 上传 App Store 的 TestFlight

```ruby
lane :beta do
  sync_code_signing(type: "appstore")    # see code signing guide for more information
  build_app(scheme: "MyApp")
  upload_to_testflight
  slack(message: "Successfully distributed a new beta build") # slack 是一款团队协作的聊天应用
end
```

## 6. [App Store 部署](https://docs.fastlane.tools/getting-started/ios/appstore-deployment/)

### 6.1 编译项目

```ruby
lane :release do
  build_app(scheme: "MyApp")
end
```

或者

```ruby
lane :release do
  build_app(scheme: "MyApp",
            workspace: "Example.xcworkspace",
            include_bitcode: true)
end
```

然后在终端的项目根目录下，运行

```shell
fastlane release
```

### 6.2 提交 App Store

```ruby
lane :release do
  capture_screenshots                  # generate new screenshots for the App Store
  sync_code_signing(type: "appstore")  # see code signing guide for more information
  build_app(scheme: "MyApp")
  upload_to_app_store                  # upload your app to App Store Connect
  slack(message: "Successfully uploaded a new App Store build")
end
```

## 7. 工作机制

### 7.1 Action

#### 7.1.1 内置 Action

每一个内置的 lane 都是一个 action。fastlane 有很多内置 lane，[这里](https://docs.fastlane.tools/actions/)列出了可用的内置 lane。

### 7.1.2 自建 Action

如果内置的 lane 不能满足你的需求，你还可以自建 lane，自建lane 的文档在[这里](https://docs.fastlane.tools/create-action/)。

### 7.2 Plugin

一般每个插件里面定义了一些相关的 action。[这里](https://docs.fastlane.tools/plugins/available-plugins/)列出了 fastlane 可以用的插件。

文档里也包含了如何使用、创建自定义 plugin。

### 7.3 使用 App Store Connect API

由于历史原因，fastlane 一开始使用 AppleID 基于 cookie 的账号密码认证方式，并且会一直支持这种方式。但是还是推荐大家使用 App Store Connect API 的验证方式。因为 App Store Connect API的验证方式有多种好处

* 没有两部认证
* 更好的性能
* 有文档化的 api
* 增加了可靠性

#### 7.3.1 创建 App Store Connect API Key

* 需要开发者账号的管理员账号才能创建，[创建链接](https://appstoreconnect.apple.com/access/api)与[创建指南](https://developer.apple.com/documentation/appstoreconnectapi/creating_api_keys_for_app_store_connect_api)。

* 创建好之后，下载 API Key 文件 (.p8格式)
  
#### 7.3.2 在 fastlane 中 使用

每个 action 单独使用

```ruby
lane :release do
  api_key = app_store_connect_api_key(
    key_id: "D383SF739",
    issuer_id: "6053b7fe-68a8-4acb-89be-165aa6465141",
    key_filepath: "./AuthKey_D383SF739.p8",
    duration: 1200, # optional (maximum 1200)
    in_house: false, # optional but may be required if using match/sigh
  )

  pilot(api_key: api_key)
end
```

或者多 action，以共享的方式使用

```ruby
lane :release do
  app_store_connect_api_key(
    key_id: "D383SF739",
    issuer_id: "6053b7fe-68a8-4acb-89be-165aa6465141",
    key_filepath: "./AuthKey_D383SF739.p8",
    duration: 1200, # optional (maximum 1200)
    in_house: false, # optional but may be required if using match/sigh
  )

  # Automatically loads Actions.lane_context[SharedValues::APP_STORE_CONNECT_API_KEY]
  pilot
end
```

或者基于 json 文件的方式使用，先创建好 json 文件，文件内容格式如下

```json
{
  "key_id": "D383SF739",
  "issuer_id": "6053b7fe-68a8-4acb-89be-165aa6465141",
  "key": "-----BEGIN PRIVATE KEY-----\nMIGTAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBHknlhdlYdLu\n-----END PRIVATE KEY-----",
  "duration": 1200, # optional (maximum 1200)
  "in_house": false, # optional but may be required if using match/sigh
}
```

然后在 fastlane 中使用

```ruby
lane :release do
  pilot( api_key_path: "fastlane/D383SF739.json" )
end
```

也可以在终端中使用

```shell
fastlane pilot distribute --api_key_path fastlane/D383SF739.json
```

### 7.4 [代码签名](https://docs.fastlane.tools/codesigning/getting-started/)

有四种代码签名的方式，首推[match](https://docs.fastlane.tools/actions/match/)

1. match
2. cert 与 sigh
3. Xcode code sign
4. Manually

### 7.5 [CI 集成](https://docs.fastlane.tools/best-practices/continuous-integration/)

CI 集成方式支持很多种，其中可以分为 Self-Hosted CIs(自己部署) 与 Hosted CIs(托管部署)两种类型。

集成工具包括但不限于

```shell
# Self-Hosted CIs
1. Jenkins
2. Gitlab
3. Bamboo
```

```shell
# Hosted CIs
1. Travis
2. Circle
3. Visula Studio
```

## 8. 文件

### 8.1 Fastfile

### 8.2 APPfile

### 8.3 Lanes

### 8.4 Actions

### 8.5 其他
