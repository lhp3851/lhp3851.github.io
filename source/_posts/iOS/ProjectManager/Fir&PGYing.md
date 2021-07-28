---
title: iOS项目管理之杂项
abbrlink: afb1c928
date: 2021-04-20 21:36:02
tags:
---
## 1. fir.im

上传至fir

```shell
fir publish ${HOME}/Desktop/Package/${IPA_NAME} -Q -T 9cfdfbd241d63197a3b83a608708e16f --password sumian
```

## 2. 蒲公英

上传至蒲公英

```shell
#curl -F "file=@${IPA_PATH}" 
      -F "uKey=******************2f5e99f3a7495" 
      -F "_api_key  - 0 : 85 =******************eb2d5cb44d93183" http://www.pgyer.com/apiv1/app/upload
```

## 3. 自建服务器交付环境

* 打包

  版本、scheme、target、workspace、profile、签名、archive、IPA

* 上传
* 下载
* 多ID分发[批量IPA包管理]
