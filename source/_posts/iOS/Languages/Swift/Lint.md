---
title: Swift Lint && Format
date: 2023-01-03 11:35:29
tags: Lint
---


## [iOS代码规范工具 SwiftLint SwiftFormat](https://juejin.cn/post/7171725810544738317#heading-1)

## [OCLint 实现 Code Review - 给你的代码提提质量](https://juejin.cn/post/6844903853775650830)

### [Sonar Rules](https://rules.sonarsource.com/objective-c/type/Code%20Smell/RSPEC-798)

## [sonar + ocLint + swiftLint 实践](https://juejin.cn/post/7026260676901339173)

xcodebuild -scheme WeSeen -workspace WeSeen.xcworkspace clean && xcodebuild -scheme WeSeen -workspace WeSeen.xcworkspace -configuration Debug | xcpretty -r json-compilation-database -o compile_commands.json

xcodebuild -scheme WeSeen -workspace WeSeen.xcworkspace clean && xcodebuild -scheme WeSeen -workspace WeSeen.xcworkspace -configuration Debug | xcpretty -r json-compilation-database -o compile_commands.json && oclint-json-compilation-database -e Pods -- -report-type xcode

xcodebuild build -workspace WeSeen.xcworkspace -scheme WeSeen -configuration Debug -sdk iphoneos | xcpretty -r json-compilation-database -o compile_commands.json

oclint-json-compilation-database -e Pods -- -report-type html -o oclintReport.html -rc LONG_LINE=9999 -max-priority-1=9999 -max-priority-2=9999 -max-priority-3=9999
