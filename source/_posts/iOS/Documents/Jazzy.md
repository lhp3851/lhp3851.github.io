---
title: iOS之文档 jazzy
abbrlink: 7c933de7
date: 2021-04-20 21:36:02
tags:
---

## 文档生成工具

```shell
Doxygen、appledoc、HeaderDoc
```

## 一、iOS 文档生成：appledoc、HeaderDoc

1、objective——C
  
```shell
appledoc Xcode script
```

### Start constants

```shell
company="gosuncn";
companyID="com.gosuncn";
companyURL="http://www.gosuncn.com/";
target="iphoneos";
#target="macosx";
outputPath="${PROJECT_DIR}";
```

### End constants
  
```shell
/usr/local/bin/appledoc \
  --project-name "doc" \
  --project-company "${company}" \
  --company-id "${companyID}" \
  --no-create-docset  \
  --output "${outputPath}" \
  --logformat xcode \
  --keep-intermediate-files \
  --no-repeat-first-par \
  --no-warn-invalid-crossref \
  --exit-threshold 2 \
  "${PROJECT_DIR}"
```

2、swift

```shell
jazzy \
  --clean \
  --author Sumian \
  --author_url <http://sumian.com/> \
  --github_url <http://192.168.1.229/hepeng.l/sm_ios_repo_base> \
  --github-file-prefix <http://192.168.1.229/hepeng.l/sm_ios_repo_base/tree/0.0.1> \
  --module-version 0.0.1 \
  --xcodebuild-arguments -scheme,sd_sdk_ios \
  --module sd_sdk_ios \
  --root-url ~/ \
  --output docs/swift_output \
  --theme docs/themes
```
