# iOS逆向工程

* [获取IPA包](~/Library/Group Containers/K36BKF7T3D.group.com..configurator/Library/Caches/Assets/TemporaryItems/MobileApps/)

* [Mac-o](http://www.cocoachina.com/mac/20150122/10988.html)
* [MachOView](https://sourceforge.net/projects/machoview/files/?source)
[iOS注入动态库](https://www.jianshu.com/p/6c45da26040d)

* [Mac install IPA](https://www.jianshu.com/p/8568a8897489)
**Package requirements (libusbmuxd >= 1.1.0) were not met:**
解决方案：

  ```shell
  brew uninstall --ignore-dependencies 
  libimobiledevice
  brew uninstall --ignore-dependencies usbmuxd
  brew install --HEAD usbmuxd
  brew unlink usbmux
  dbrew link usbmuxd
  brew install --HEAD libimobiledevice
  ```

* [libimobiledevice 源码](https://github.com/libimobiledevice)

idevice
atos
otool
sigh
mokeyDev、OpenDev
TheOS
rvictl
wireshark
charles
----------------iOS逆向-------------------
要求：
  “硬件构成、iOS系统的运行原理，还要具备丰富的iOS开发经验。”

逆向作用：
  恶意软件
  去除限制
  评定安全等级
  检查后门
  逆向iOS SDK？
  借鉴
    WireLurker

病毒：
  Ikee -> iOS：alpine
  WireLurker
  
Cydia:
  xsellize
  iFile（MAcOS: AFC2、iFunBox）
  SMSNinja

团队：
“evad3rs、盘古、太极”

ios 逆向工具：
  1、监测工具
    Reveal
    snoop-it
    introspy

  2、反汇编工具（disassembler）
    IDA
    Hopper

  3、调试工具（debugger）
    LLDB
    LLVM

  4、以及开发工具
    iOSOpenDev（Xcode）
    TheOS（command line）

  sudo plutil -p smartpark.app/Info.plist | grep CFBundleIdentifier
  "CFBundleIdentifier" => "com.jieshun.hatc"

iOS高级安全工程师/专家
岗位要求
1.熟悉IDA Pro、GDB、JEB、lldb等常用逆向分析工具，具备较强的逆向分析能力，熟悉ARM、x86/64等指令集；
2.熟练掌握应用逆向的静态分析、动态调试、代码跟踪等；
3.负责对接业务安全需求与工具研发；
4.熟悉C/C++、Objective-C、python语言之中一个或多个；熟悉各种通用加密算法；
5.良好的逻辑思维能力和团队合作精神，善于交流和表达；

加分项：
1.有一定的iOS越狱开发经验；
2.有安全编程相关经验, 熟悉业务安全技术对抗的常见技术手段；
3.多平台逆向经验(iOS/Android/Windows)
4.了解业务安全黑灰产；

工作地点：北京/杭州
简历请投: lanjun007@alibaba-inc.com (简历快到碗里来吧)

公司信息
上海某广告公司

联系方式
电话:13818882062

职位名称
iOS逆向工程师

职位职责
网络协议层逆向兼顾iOS远程控制开发

职位要求
0.2-3年iOS开发经验
1.静态分析 IDA pro、Hopper Disassembler
2.动态分析 lldb、cycript、frida
3.网络分析 Charles(https)、Wireshark(socket)
4.视图分析 Reveal、Flex
5.编译工具 clang、cmake、theos、
6.注入工具 cynject、yololib、insert_dylib、optool、install_name_tool
7.砸壳工具 clutch、dumpdecrypted、dumpexec
8.Hook工具 MobileSubstrate、fishhook、HookZz、substitute、libcapstone
9.基础技能 签名、脱壳、class-dump、常用的命令行工具例如ssh、ps等
10.熟悉SpringBoard以及它依赖的framework加分
a.熟悉VideoToolBox编解码加分
b.熟悉Unity3D和cocos2D逆向或者正向开发加分
c.熟悉AppStore以及它交互的几个进程加分
d.自我驱动力强，态度比能力更重要
e.邮箱地址 请调试该app <https://www.pgyer.com/crackme_> 15
PS:0和d是硬性要求，不过要是0-1年时间技能到达了2-3年的也ok，还会加分。1-9项中的工具，单独掌握一种即可，自己研发的加分。a-c的经验多多益善

工作地点: 上海徐汇
简历请投: 参考e项
