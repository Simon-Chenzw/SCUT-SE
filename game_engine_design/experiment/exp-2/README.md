# 类
- [World.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/Engine/World.h) Line 894
  - 成员：声明 3k 行 ***TL;DR***
  - World 是表示地图或沙盒的顶级对象，Actor 和组件将在其中存在并被渲染。
    一个世界可以是一个单一的持久关卡，其中包含一个可选的流式关卡列表，这些关卡通过卷和蓝图函数加载和卸载，或者它可以是一个用世界组合组织的关卡集合。
  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/UWorld/

- [Level.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/Engine/Level.h) Line 412
  - 成员：声明 600 行 ***TL;DR***
  - 关卡对象。包含关卡的 AActor 列表、BSP 信息和画笔列表。每个关卡都有一个 World 作为其 Outer，并且可以用作 PersistentLevel，但是，当一个关卡在 OwningWorld 中流式传输时，它代表它所属的 World。关卡是一组 Actor（灯光、体积、网格实例等）。可以将多个关卡加载和卸载到世界中以创建流媒体体验。
  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/ULevel/


- [Actor.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h) Line 132
  - 成员：声明 3k+ 行 ***TL;DR***
  - Actor 是可以在关卡中放置或生成的 Object 的基类。Actor 可能包含一组 ActorComponent，可用于控制 Actor 如何移动、如何渲染等。Actor 的另一个主要功能是能通过网络复制属性和函数调用。
  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/


# 主要关系
- UWorld: 包含一个单一的持久关卡，还有可选的流式关卡列表
  <!-- ULevel -->
  - Level 管理
    - `TArray<class ULevel*> Levels;`
      - 当前在这个世界上的一系列 ULevel
    - `const TArray<class ULevel*>& GetLevels() const;`
      - 返回 ULevel 列表
    - `bool AddLevel( ULevel* InLevel );`
      - 添加 ULevel 到列表中
    - `bool RemoveLevel( ULevel* InLevel );`
      - 从列表中删除指定的 ULevel
    - `ULevel* GetLevel( int32 InLevelIndex ) const;`
      - 返回指定序号的 ULevel
  	- `bool ContainsLevel( ULevel* InLevel ) const;`
      - 返回是否包含指定的 ULevel
  - 持久 Level
    - `ULevel* PersistentLevel;`
      - 包含世界信息、默认画笔和在游戏过程中生成的 AActor 等内容的持久关卡
    - `class ULevel* GetCurrentLevel() const;`
      - 获取当前世界的 ULevel
  - 流式 Level
    - `TArray<ULevelStreaming*> StreamingLevels;` （略过）
      - 流式关卡列表。Level 集合。 ULevel 由 FName（包名）引用以避免序列化引用。 还包含世界单位的偏移量
  - Level 显示管理
    - `class ULevel* CurrentLevelPendingVisibility;`
      - 指向队列中要显示的当前 ULevel 的指针，如果没有待处理，则为 NULL
    - `ULevel* GetCurrentLevelPendingVisibility() const { return CurrentLevelPendingVisibility; }`
      - 返回显示过程中的 ULevel（如果有）
  	- `class ULevel* CurrentLevelPendingInvisibility;`
      - 指向队列中要设为不可见的当前 ULevel 的指针，如果没有待处理，则为 NULL
  	- `ULevel* GetCurrentLevelPendingInvisibility() const { return CurrentLevelPendingInvisibility; }`
      - 返回隐藏过程中的 ULevel（如果有）	
  - utils
    - `void ModifyLevel(ULevel* Level) const;`
      - 修改指定的 ULevel
  - 编辑器 Utils
    - `void AddToWorld( ULevel* Level, const FTransform& LevelTransform = FTransform::Identity, bool bConsiderTimeLimit = true );`
      - 将传入的 ULevel 与 UWorld 相关联
    - `void RemoveFromWorld( ULevel* Level, bool bAllowIncrementalRemoval = false );`
      - 将传入的 ULevel 与 UWorld 分离
  <!-- AActor -->
  - Actor 管理
    - `AActor* SpawnActor( UClass* InClass, FVector const* Location=NULL, FRotator const* Rotation=NULL, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters() );`
      - 创建 Actor
    - `AActor* SpawnActor( UClass* Class, FTransform const* Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters());`
      - 创建 Actor
    - `AActor* SpawnActorAbsolute( UClass* Class, FTransform const& AbsoluteTransform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters());`
      - 创建 Actor
    - `T* SpawnActorDeferred(UClass* Class, FTransform const& Transform, ...)`
      - 创建 Actor
    - `bool ContainsActor( AActor* Actor ) const;`
      - 返回传入的actor是否是任何加载的关卡actor数组的一部分
    - `void RemoveActor( AActor* Actor, bool bShouldModifyLevel ) const;`
      - 从 AActor 列表中删除传入的 AActor 
    - `bool DestroyActor( AActor* Actor, bool bNetForce=false, bool bShouldModifyLevel=true );`
      - 从其关卡的actor列表中删除actor并清理引擎的内部状态
    - `bool EditorDestroyActor( AActor* Actor, bool bShouldModifyLevel );`
      - 编辑器中调用的 DestroyActor() 包装器
  - 相机 Actor
    - `void RegisterAutoActivateCamera(ACameraActor* CameraActor, int32 PlayerIndex);`
      - 注册一个为 PlayerController 自动激活的 CameraActor。
  - 网络 Actor
    - `void AddNetworkActor( AActor* Actor );`
      - 添加网络 Actor
    - `void RemoveNetworkActor( AActor* Actor ) const;`
      - 删除网络 Actor
- ULevel: 包含关卡的 AActor 列表、BSP 信息和画笔列表。每个关卡都有一个 World 作为其 Outer。关卡是一组 Actor（灯光、体积、网格实例等）。可以将多个关卡加载和卸载到世界中以创建流媒体体验。
  - Actor 管理
    - `TArray<AActor*> Actors;`
      - 此 ULevel 中所有 AActor 的数组, 由 FActorIteratorBase 和派生类使用
    - `TArray<AActor*> ActorsForGC;`
      - 在此级别中要暴露于 GC 的 AActor 数组。 所有其他actor都将通过 ULevelActorContainer 引用
  - Utils
    - `static bool IsNetActor(const AActor* Actor);`
      - 在内部用于确定哪些 AActor 应该进入 UWorld 的 NetworkActor 列表
    - `void CreateReplicatedDestructionInfo(AActor* const Actor);`
      - 在 DestroyedReplicatedStaticActors 列表中填充一个 Actor 的实例
    - `void RegisterActorForAutoReceiveInput(AActor* Actor, const int32 PlayerIndex);`
      - 注册一个应该在创建玩家输入堆栈时添加到玩家输入堆栈的actor

# 具体代码
- UWorld::SpawnActor [LevelActor.cpp](../UnrealEngine/Engine/Source/Runtime/Engine/Private/LevelActor.cpp) Line 308 ~ 594
``` c++
// 先进行 Class 检查
// actually make the actor object
AActor* const Actor = NewObject<AActor>(LevelToSpawnIn, Class, NewActorName, ActorFlags, Template, false, nullptr, ExternalPackage);  // Line 508
// 在进行 Actor 检查
LevelToSpawnIn->Actors.Add( Actor );    // Line 539
LevelToSpawnIn->ActorsForGC.Add(Actor); // Line 540
return Actor;                           // Line 593
```