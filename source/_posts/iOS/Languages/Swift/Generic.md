---
title: iOS编程语言之 swift 泛型
abbrlink: 91541ff5
date: 2021-07-23 17:10:02
tags:
---

## 1. [泛型](https://swiftgg.gitbook.io/swift/swift-jiao-cheng/22_generics#extending-a-generic-type)

类型参数  -->  类型参数遵循约束

关联类型  -->  关联类型遵循约束

协议  -->  关联类型协议（泛型协议）

泛型类型：泛型函数、泛型类（遵循泛型协议）、泛型协议、泛型下表

拓展（extension）里的泛型，拓展中包含类型参数，并且可以给类型参数加（调用山下文）约束（通过 where）。

```Swift
protocol Container {
  associatedtype Item: Equatable
  mutating func append(_ item: Item)
  var count: Int { get }
  subscript(i: Int) -> Item { get }
}

protocol SuffixableContainer: Container {
  associatedtype Suffix: SuffixableContainer where Suffix.Item == Item
  func suffix(_ size: Int) -> Suffix
}

extension Stack: SuffixableContainer {
  // 推断 suffix 结果是Stack。
  func suffix(_ size: Int) -> Stack {
      var result = Stack()
      for index in (count-size)..<count {
          result.append(self[index])
      }
      return result
  }
}
var stackOfInts = Stack<Int>()
stackOfInts.append(10)
stackOfInts.append(20)
stackOfInts.append(30)
let suffix = stackOfInts.suffix(2)
```