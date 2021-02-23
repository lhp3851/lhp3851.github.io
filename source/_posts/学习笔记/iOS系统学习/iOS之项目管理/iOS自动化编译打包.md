Information about project "_Pods":
    Targets:
        Pods-sm_ios_base_Example
        Pods-sm_ios_base_Tests
        sm_ios_base

    Build Configurations:
        Debug
        Release

    If no build configuration is specified and -scheme is not passed then "Release" is used.

    Schemes:
        Pods-sm_ios_base_Example
        Pods-sm_ios_base_Example
        Pods-sm_ios_base_Tests
        Pods-sm_ios_base_Tests
        sm_ios_base
        sm_ios_base



xcodebuild -workspace sm_ios_base.xcworkspace -scheme sm_ios_base-Example -configuration Debug

xcodebuild -project _Pods.xcodeproj -target sm_ios_base  -configuration Debug
