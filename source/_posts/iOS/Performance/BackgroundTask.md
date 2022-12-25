---
title: Background Task
abbrlink: 49417
date: 2021-09-24 15:20:02
tags:
---

## 1. iOS 后台任务

### 1.1 Background Task

在应用切换到后台之后，很有可能被系统杀掉，因此切换到后台的时候需要保存重要数据，可以借助 Background Task。

```objc
[self.timer invalidate];
self.timer = nil;
[[UIApplication sharedApplication] endBackgroundTask:self.taskId];
self.taskId = UIBackgroundTaskInvalid;
}];
```

### 1.1.1 [Background Tasks](https://developer.apple.com/documentation/backgroundtasks)

iOS 13 之后，出了个新 api，可以根据情况处理后台任务。

这种类型的后台任务需要在 App 的 capability 里设置，并在 plist 里面注册，然后在代码里面配置。

### 1.2 Background Fetch

Background Fetch可以让App没有启动或者在后台的时候，周期性的获取数据。

```objective-c
// APP 启动的时候注册
[[UIApplication sharedApplication] setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];

-(void)application:(UIApplication *)application performFetchWithCompletionHandler:(nonnull void (^)(UIBackgroundFetchResult))completionHandler{

    // 请求数据
    completionHandler(UIBackgroundFetchResultNewData);
}
```

在 run 的配置上，将`launch due to background fetch event`勾上，然后点击Run按钮启动应用。

**注意：** 用户主动杀死App的情况，Background Fetch不会工作。

### 1.3 Background Download

创建 background session

```objc
- (NSURLSession *)backgroundSession
{
    static NSURLSession *session = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration backgroundSessionConfigurationWithIdentifier:@"com.example.apple-samplecode.SimpleBackgroundTransfer.BackgroundSession"];
        session = [NSURLSession sessionWithConfiguration:configuration delegate:self delegateQueue:nil];
    });
    return session;
}
```

创建后台下载任务

```objc
NSURL *downloadURL = [NSURL URLWithString:DownloadURLString];
NSURLRequest *request = [NSURLRequest requestWithURL:downloadURL];
self.downloadTask = [self.session downloadTaskWithRequest:request];
[self.downloadTask resume];
```

在回调中处理后台下载数据

```objc
// 处理下载进度
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite
{
    
}

// 下载任务完成回调
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(NSURL *)downloadURL
{
    
}

// 下载失败回调
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error
{
    
}

// 处理下载任务由于网络原因失败后被系统恢复的回调
-(void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didResumeAtOffset:(int64_t)fileOffset expectedTotalBytes:(int64_t)expectedTotalBytes
{
    
}
```

当App不在运行时，因为后台下载任务是重启的一个进程处理，所以当任务完成或者请求证书验证时，系统会重新启动并进入后台处理后台会话时间。在这里，你应该保存`completionHandler`以便在处理完事件时告诉系统重新进入暂停状态。你还可以使用后台会话标识来重新创建后台会话，这个会话会关联之前的会话进程。

```objc

- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier
  completionHandler:(void (^)(void))completionHandler
{
    BLog();

    self.backgroundSessionCompletionHandler = completionHandler;
}

- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession *)session
{
    dispatch_async(dispatch_get_main_queue(), ^{
        APLAppDelegate *appDelegate = (APLAppDelegate *)[[UIApplication sharedApplication] delegate];
        if (appDelegate.backgroundSessionCompletionHandler) {
            void (^completionHandler)() = appDelegate.backgroundSessionCompletionHandler;
            appDelegate.backgroundSessionCompletionHandler = nil;
            completionHandler();
        }
        
        NSLog(@"All tasks are finished");
    });
}

```

### 1.4 特定的后台任务

如音乐播放、后台持续定位、VoIP、蓝牙等，这些场景要在 APP 的 capability 设置里设置。

```objc
-(void)applicationWillResignActive:(UIApplication *)application
{
  //开启后台处理多媒体事件
  [[UIApplication sharedApplication]   beginReceivingRemoteControlEvents];
AVAudioSession *session=[AVAudioSession sharedInstance];
  [session setActive:YES error:nil];
  //后台播放
  [session setCategory:AVAudioSessionCategoryPlayback error:nil];
  //这样做，可以在按home键进入后台后 ，播放一段时间，几分钟吧。但是不能持续播放网络歌曲，若需要持续播放网络歌曲，还需要申请后台任务id，具体做法是：
  _bgTaskId=[AppDelegate backgroundPlayerID:_bgTaskId];
  //其中的_bgTaskId是后台任务UIBackgroundTaskIdentifier _bgTaskId;
}

实现一下backgroundPlayerID:这个方法:
+(UIBackgroundTaskIdentifier)backgroundPlayerID:(UIBackgroundTaskIdentifier)backTaskId
{
  //设置并激活音频会话类别
  AVAudioSession *session=[AVAudioSession sharedInstance];
  [session setCategory:AVAudioSessionCategoryPlayback error:nil];
  [session setActive:YES error:nil];
  //允许应用程序接收远程控制
  [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];
  //设置后台任务ID
  UIBackgroundTaskIdentifier   newTaskId=UIBackgroundTaskInvalid;
newTaskId=[[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:nil];
  if(newTaskId!=UIBackgroundTaskInvalid&&backTaskId!=UIBackgroundTaskInvalid)
{
  [[UIApplication sharedApplication] endBackgroundTask:backTaskId];
}
  return newTaskId;
}
```

处理中断事件，如电话，微信语音等。

```objc
//在通知中心注册一个事件中断的通知，处理中断事件的通知
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleInterreption:) name:AVAudioSessionInterruptionNotification object:[AVAudioSession sharedInstance]];

//实现接收到中断通知时的方法，处理中断事件
-(void)handleInterreption:(NSNotification *)sender
{
  if(_played) {
     [self.playView.player pause];
     _played=NO;
  } else {
     [self.playView.player play];
     _played=YES;
  }
}
```

### 1.5 静默推送，推送唤醒

普通推送，系统收到推送消息之后，应用程序并不做任何事情，等待用户操作。静默推送，在系统收到推送之后，唤起App，App的 `didReceiveRemoteNotification` 方法被调用，在这个方法中可以发起一个网络请求，下载数据。
静默推送只需要在普通推送的payload中增加一个`content-available的key`：

```json
{
"aps":
    { 
    "content-available":1,
    "alert":"This is some fancy message2.",
    "badge":6,
    "sound": "default"
    }
}
```

接受远程通知

```objc
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    NSLog(@"iOS7及以上系统，收到通知:%@", userInfo);
    completionHandler(UIBackgroundFetchResultNewData);
}
```

静默推送唤起的任务最多执行30s的时间，completionHandler必须被调用，告诉系统任务执行完毕。
另外，在用户点击了推动消息启动了应用之后，didReceiveNotificationResponse这个方法会被调用，因此要注意数据的处理是否会和didReceiveRemoteNotification重复。

```objc
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)())completionHandler{
    completionHandler(); // 系统要求执行这个方法
}
```

同样，如果用户主动杀死了App，静默推送也不会起作用。

如果你一点也不想让你的应用在后台执行，你可以显示地在info.plist中添加key `UIApplicationExitsOnSuspend`（并且设置成YES）。When an app opts out, it cycles between the not-running, inactive, and active states and never enters the background or suspended states. 当用户按下home键退出应用时，应用的代理方法`applicationWillTerminate:`被调用，并且在应用终止前有大约5s的时间去清理工作。
