- [Actor.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h) Line 132
  - 成员：声明 3k+ 行 ***TL;DR***
  - Actor 是可以在关卡中放置或生成的 Object 的基类。Actor 可能包含一组 ActorComponent，可用于控制 Actor 如何移动、如何渲染等。Actor 的另一个主要功能是能通过网络复制属性和函数调用。
  - Actor初始化有多个步骤，下面是重要的虚函数被调用的顺序：

    - UObject::PostLoad：对于静态放置在关卡中的演员，普通的UObject PostLoad 在编辑器和游戏过程中都会被调用。这不适用于新生成的演员。

    - UActorComponent::OnComponentCreated：当一个actor在编辑器中或游戏过程中生成时，它会被任何原生组件调用。对于蓝图创建的组件，它会在该组件的构造过程中被调用。对于从关卡加载的组件，不需要这样做。

    - AActor::PreRegisterAllComponents：对于静态放置的actors和具有本地根组件的衍生actors，现在调用它。对于没有原生根组件的蓝图 Actor，这些注册函数会在构建过程中稍后调用。

    - UActorComponent::RegisterComponent：所有组件都在编辑器中注册，并在运行时创建它们的物理/视觉表示。这些调用可能分布在多个帧上，但总是在 PreRegisterAllComponents 之后。在 UnregisterComponent 调用将其从世界中删除后，这也可能会在稍后被调用。

    - AActor::PostRegisterAllComponents：在编辑器和游戏中为所有actor调用，这是所有情况下调用的最后一个函数。

    - AActor::PostActorCreated：当在编辑器中或在游戏过程中创建一个演员时，它会在构造之前被调用。对于从关卡加载的组件，不需要这样做。

    - AActor::UserConstructionScript：调用实现构造脚本的蓝图。

    - AActor::OnConstruction：在ExecuteConstruction结束时调用，调用蓝图构建脚本。在所有蓝图创建的组件都完全创建和注册后调用。这仅在生成的 Actor 的游戏过程中调用，并且在更改蓝图时可能会在编辑器中重新运行。

    - AActor::PreInitializeComponents：在对actor的组件调用 InitializeComponent 之前调用。这仅在游戏过程中和某些编辑器预览窗口中调用。

    - UActorComponent::Activate：仅当组件设置了 bAutoActivate 时才会调用它。如果手动激活组件，稍后也会调用它。

    - UActorComponent::InitializeComponent：仅当组件具有 bWantsInitializeComponentSet 时才会调用它。这仅在每个游戏会话中发生一次。

    - AActor::PostInitializeComponents：在actor的组件初始化后调用，仅在游戏和一些编辑器预览期间调用。

    - AActor::BeginPlay：在关卡开始计时时调用，仅在实际游戏过程中调用。这通常发生在 PostInitializeComponents 之后，但对于网络或子角色可能会延迟。

  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/

- [ActorComponent.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/Components/ActorComponent.h) Line 116
  - 成员：声明 1k 行 ***TL;DR***
  - ActorComponent 是定义可重用行为的组件的基类，这些行为可以添加到不同类型的 Actors 中。具有变换的 ActorComponents 称为 SceneComponents，而那些可以渲染的是 PrimitiveComponents。
  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Components/UActorComponent/

- [SceneComponent.h](../UnrealEngine/Engine/Source/Runtime/Engine/Classes/Components/SceneComponent.h)
  - 成员：声明 1k 行 ***TL;DR***
  - USceneComponent 具有变换和支持附件，但没有渲染或碰撞功能。用作层次结构中的“虚拟”组件。
  - API Reference： https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Components/USceneComponent/

# 主要关系
- AActor: 可以在关卡中放置或生成的 Object 的基类，Actor 可能包含一组 ActorComponent
  - `USceneComponent* RootComponent;`
  - `TArray<UActorComponent*> ReplicatedComponents;`
  - `TSet<UActorComponent*> OwnedComponents;`
  - `TArray<UActorComponent*> InstanceComponents;`
  - `TArray<UActorComponent*> BlueprintCreatedComponents;`
- UActorComponent: 定义可重用行为的组件的基类，这些行为可以添加到不同类型的 Actors 中。
- USceneComponent: 具有变换和支持附件，但没有渲染或碰撞功能。是 Component 中较为重要的种类
  - `USceneComponent* AttachParent;`
  - `TArray<USceneComponent*> AttachChildren;`
  - `TArray<USceneComponent*> ClientAttachedChildren;`
  - `FVector RelativeLocation;`
  - `FRotator RelativeRotation;`

# 关键设计
## UActorComponent 的关系
Component 不提供嵌套的功能，所有的 Component 只能挂载在 Actor 下。

从功能上来说，UE更倾向于编写功能单一的Component（如UMovementComponent）, 而不是一个整合了其他Component的大管家Component。
而从游戏逻辑的实现来说，UE也是不推荐把游戏逻辑写在Component里面，所以也没什么机会去写一个很复杂的Component.

## USceneComponent 的嵌套
很多其他游戏引擎，有一种设计思路是“万物皆Node”。Node都带变换。

比如说你要设计一辆汽车，一种方式是车身作为一个Node,4个轮子各为车身的子Node，然后移动父Node来前进。
而在UE里，一种很可能的方式就变成，汽车是一个Actor，车身作为RootComponent，4个轮子都作为RootComponent的子SceneComponent。

UE 里通过组合 Component 来达到组合物体的功能。而这个组合体，再由一个统一的Actor对外提供逻辑功能。从而减轻组合复制物件的开销。

# 关键函数
## AActor：获取坐标，通过转发至 RootComponent 的方式获取坐标

```c++
  /** Returns the location of the RootComponent of this Actor*/ 
  FORCEINLINE FVector GetActorLocation() const
  {
    return TemplateGetActorLocation(RootComponent);
  }

  template<class T>
	static FORCEINLINE FVector TemplateGetActorLocation(const T* RootComponent)
	{
		return (RootComponent != nullptr) ? RootComponent->GetComponentLocation() : FVector::ZeroVector;
	}
```

类似的还有 Input 事件，也是转发至 InputComponent: `class UInputComponent* InputComponent;`
