---
title: Git 规范
date: 2021-04-20 21:36:02
tags:  
---

commit代码规范

基本样式：[type] [module] : --bug=1000627 Message

//空一行

detail

//空一行

说明：

其中：
type, module 和 message 是必选。
detail 为可选。

type 用于说明 commit 的类别，使用下面标识：
  bug-fix：修复bug

  feature：新功能实现

  optimize：重构，优化，工程配置等

  merge: 用于替换自动生成合并分支log

module 用于说明commit内容所属的业务模块（如果不属于任何模块，使用“通用”）

message 修改的内容

detail 用于在该commit有多条内容的时候，加以说明
bug-fix需要添加关键字：--bug=bugid
feature需要添加关键字：--story=storyid

样例1、

[fixbug] [咨询] : 修复会话页面在iOS10上显示异常的问题

样例2、

[fixbug] [咨询] [tapd id: 1009080,1090900] : 修复以下bug：

1.修复会话页面在iOS10上显示异常的问题

2.修复tabbarItem小红点显示逻辑不正确bug

3.修复navigationbar高度不正确的问题

样例3、

[feature] [登陆] : 导入微信SDK，实现微信登陆

样例4、

[optimize] [工程配置] : 增加会话创建失败后的重连，降低失败概率

样例5、

[merge] : Merge branch 'releaseV0.2.0' into ‘develop’
