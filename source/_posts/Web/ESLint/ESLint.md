---
title: ESLint
date: 2022-01-10 21:56:40
tags: ESLint
---


## 1. [Eslint 超简单入门教程](https://www.jianshu.com/p/ad1e46faaea2)

## 2. [ESLint 使用教程](https://juejin.cn/post/7012798266089668645#heading-18)

## 3. ESLint

### 3.1 [ESLint](https://eslint.org)

### 3.2. [ESLint 中文](http://eslint.cn)

## 4. 工具

### 4.1 Prettier

[代码风格最佳实践](https://juejin.cn/post/7018488201295691789/)

### 4.2 Beautify

## 5. [eslint-config-airbnb](https://www.npmjs.com/package/eslint-config-airbnb)

## 6. [eslint-plugin-react](https://github.com/yannickcr/eslint-plugin-react)

## 7. [ESLint VSCode Plugin](https://marketplace.visualstudio.com/items?itemName=dbaeumer.vscode-eslint)

## 8. 概念

### 8.1 语言环境

env
globals
parser
parseOptions

### 8.2 插件

plugins

### 8.3 规则

rules

### 8.4 继承

extend

### 8.5 忽略

ignorePatterns

### 8.6 覆盖

overrides 规则

### 8.7 Glob 匹配

```json
/* ./src 目录下除了 a.js 下的 js 文件应用 no-alert 规则 */
{
  "overrides": [
    {
      "files": ["src/*.js"],
      "excludedFiles": "a.js",
      "rules": {
        "no-alert": "warn"
      }
    }
  ]
}
```

### 8.8 注释配置
