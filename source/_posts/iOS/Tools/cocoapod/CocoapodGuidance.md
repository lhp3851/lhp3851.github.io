---
title: Cocoapod 指南
abbrlink: cbdca039
date: 2021-04-20 21:36:02
tags:
---
## 一、pod 公开库

### 1. 索引库

#### 1.1 添加索引库

```shell
pod repo add WTSpecs https://coding.net/wtlucky/WTSpecs.git
```

#### 1.2 删除索引库

```shell
pod repo remove WTSpecs
```

#### 2. pod库

##### 2.1 创建pod库

```shell
pod lib create podTestLibrary
```

##### 2.2 添加到远程

```shell
git add .
git commit -s -m "Initial Commit of Library"
git remote add origin git@coding.net:wtlucky/podTestLibrary.git
git push origin master
```

##### 2.3 打tag

```shell
git tag -a 0.1.0 -m "first release"
git push --tags / git push origin tag 0.1.0
```

##### 2.4 修改podspec文件

##### 2.5 检验pod库、podspec

```shell
pod lib lint
```

##### 2.6 提交pod库

```shell
pod repo push WTSpecs PodTestLibrary.podspec  #前面是本地Repo名字 后面是podspec名字
```

##### 2.7 检索pod库

```shell
pod search PodTestLibrary
```

##### 2.8 使用pod库

```shel
pod 'PodTestLibrary', '~> 0.1.0'
```
  
## 二、私有库

### 1. 检验
  
```shell
pod lib lint --allow-warnings --sources=<https://github.com/aliyun/aliyun-specs.git,https://github.com/CocoaPods/Specs.git>
```

### 2. 远程检验
  
```shell
pod spec lint --allow-warnings --sources=<https://github.com/aliyun/aliyun-specs.git,https://github.com/CocoaPods/Specs.git>
```

### 3. 提交

```shell
pod repo push sumian sm_ios_base.podspec --allow-warnings --sources='http://192.168.1.229/rysn/sm_ios_index_repo.git,https://github.com/aliyun/aliyun-specs.git,https://github.com/CocoaPods/Specs'
```

## 3. pod 命令

```shell
Usage:

    $ pod COMMAND

      CocoaPods, the Cocoa library package manager.

Commands:

    + cache         Manipulate the CocoaPods cache
    + deintegrate   Deintegrate CocoaPods from your project
    + env           Display pod environment
    + init          Generate a Podfile for the current directory
    + install       Install project dependencies according to versions from a
                    Podfile.lock
    + ipc           Inter-process communication
    + lib           Develop pods
    + list          List pods
    + outdated      Show outdated project dependencies
    + package       Package a podspec into a static library.
    + plugins       Show available CocoaPods plugins
    + repo          Manage spec-repositories
    + search        Search for pods
    + setup         Setup the CocoaPods environment
    + spec          Manage pod specs
    + trunk         Interact with the CocoaPods API (e.g. publishing new specs)
    + try           Try a Pod!
    + update        Update outdated project dependencies and create new Podfile.lock

Options:

    --silent        Show nothing
    --version       Show the version of the tool
    --verbose       Show more debugging information
    --no-ansi       Show output without ANSI codes
    --help          Show help banner of specified command
```

## 4. pod lib lint 命令

```shell
Usage:

    $ pod lib lint

      Validates the Pod using the files in the working directory.

Options:

    --quick                                           Lint skips checks that would
                                                      require to download and build
                                                      the spec
    --allow-warnings                                  Lint validates even if warnings
                                                      are present
    --subspec=NAME                                    Lint validates only the given
                                                      subspec
    --no-subspecs                                     Lint skips validation of
                                                      subspecs
    --no-clean                                        Lint leaves the build directory
                                                      intact for inspection
    --fail-fast                                       Lint stops on the first failing
                                                      platform or subspec
    --use-libraries                                   Lint uses static libraries to
                                                      install the spec
    --use-modular-headers                             Lint uses modular headers during
                                                      installation
    --sources=https://github.com/artsy/Specs,master   The sources from which to pull
                                                      dependent pods (defaults to
                                                      https://github.com/CocoaPods/Specs.git).
                                                      Multiple sources must be
                                                      comma-delimited.
    --platforms=ios,macos                             Lint against specific
                                                      platforms(defaults to all
                                                      platforms supported by the
                                                      podspec).Multiple platforms must
                                                      be comma-delimited
    --private                                         Lint skips checks that apply
                                                      only to public specs
    --swift-version=VERSION                           The SWIFT_VERSION that should be
                                                      used to lint the spec. This
                                                      takes precedence over a
                                                      .swift-version file.
    --skip-import-validation                          Lint skips validating that the
                                                      pod can be imported
    --skip-tests                                      Lint skips building and running
                                                      tests during validation
    --silent                                          Show nothing
    --verbose                                         Show more debugging information
    --no-ansi                                         Show output without ANSI codes
    --help                                            Show help banner of specified
                                                      command
```

## 5. pod 修改工程配置

```shell
post_install do |installer_representation|

    installer_representation.pods_project.targets.each do |target|
        target.build_configurations.each do |config|
            #去警告
            config.build_settings['GCC_WARN_INHIBIT_ALL_WARNINGS'] = 'YES'
            #判断scheme
            if config.name.include?("SchemeAppTest_Release")
                #添加scheme对应的预编译宏
                config.build_settings['GCC_PREPROCESSOR_DEFINITIONS'] ||= ['$(inherited)']
                config.build_settings['GCC_PREPROCESSOR_DEFINITIONS'] << 'SCHEMEAPPTESTRELEASE=3'
            end
            if config.name.include?("SchemeAppTest_Debug")
                config.build_settings['GCC_PREPROCESSOR_DEFINITIONS'] ||= ['$(inherited)']
                config.build_settings['GCC_PREPROCESSOR_DEFINITIONS'] << 'SCHEMEAPPTESTDEBUG=2'
                #指定scheme的调试模式可见变量
                config.build_settings['GCC_OPTIMIZATION_LEVEL'] = '0'
                #某些情况由于编译器不支持无法debug（可选）
                config.build_settings['ONLY_ACTIVE_ARCH'] = 'YES'
            end
          end
    end    
end
  ```
