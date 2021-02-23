1、日志内容

    时间|日志级别|类名_函数名_行数|分类|Log内容
    
获取类名：
```
extension NSObject {
    var className: String {
        return String(describing: type(of: self)).components(separatedBy: ".").last!
    }

    class var className: String {
        return String(describing: self).components(separatedBy: ".").last!
    }
}
```

生成log函数：
```
public func createLog(level: DebugLevel, targetClass: AnyClass, type: OperateType, content: String,  _ line: Int = #line, _ function: String = #function)
-> String {
    let lineStr = String.init(format: "line:%d", line)
    let levelStr = levelToString(level: level)
    let separator = "|"
    let classSeparator = "_"
    let log: String = Date().toString() + separator + levelStr + separator + targetClass.className + classSeparator + function + classSeparator + lineStr + separator + content + "\n"
    print(log)
    return log
}
```

日志文件操作：
```
public protocol LogStorageProtocol {

    /// 获取日志缓存地址
    ///
    /// - Returns: String
    func getCachePath() -> String

    /// 删除文件
    ///
    /// - Parameter fileName: String
    /// - Returns: Bool
    func deleteFile(fileName: String) -> Bool

    /// 清除全部日志缓存
    ///
    /// - Returns: Bool
    func cleanCache() -> Bool

    /// 读取日志文件
    ///
    /// - Parameter fileName: String
    /// - Returns: Data
    func readFile(fileName: String) -> Data?

    /// 更新写入Log数据
    ///
    /// - Parameters:
    ///   - fileName: String
    ///   - data: Data
    /// - Returns: Data
    func updateFile(fileName: String, data: Data) -> Bool

    /// 自动根据天数创建文件名
    ///
    /// - Returns: String
    func createFileName() -> String
}
```

策略：

    而这个十条一写，没有达到标准的就暂时保存在内存里，我的想法是创建一个循环队列，
    根据FIFO原则，当满足十条Log时，做一次写入操作，而循环队列在空间上是非常节省
    资源的，如果没有满足十条日志，那就都暂存在队列里，整个开销就是循环队列的一个数
    组，容量是11个元素，还有一个充当哨兵
    
    
* [**自主设计日志系统**](https://www.jianshu.com/p/74f121bfd9e9)