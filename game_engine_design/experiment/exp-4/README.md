# Tick 机制

## UWorld::Tick

### GuardedMain
[Launch.cpp](../UnrealEngine/Engine/Source/Runtime/Launch/Private/Launch.cpp)
```c++
int32 GuardedMain( const TCHAR* CmdLine )
{
    /* ... */
	BootTimingPoint("Tick loop starting");
	DumpBootTiming();

	// Don't tick if we're running an embedded engine - we rely on the outer
	// application ticking us instead.
	if (!GUELibraryOverrideSettings.bIsEmbedded)
	{
		while( !IsEngineExitRequested() )
		{
			EngineTick();
		}
	}

	TRACE_BOOKMARK(TEXT("Tick loop end"));
    /* ... */
}
```

### EngineTick
[Launch.cpp](../UnrealEngine/Engine/Source/Runtime/Launch/Private/Launch.cpp)
```c++
FEngineLoop	GEngineLoop;

/** 
 * Ticks the engine loop 
 */
LAUNCH_API void EngineTick( void )
{
	GEngineLoop.Tick();
}
```

### FEngineLoop::Tick()
[LaunchEngineLoop.cpp](../UnrealEngine/Engine/Source/Runtime/Launch/Private/LaunchEngineLoop.cpp)
```c++
void FEngineLoop::Tick()
{
    /* ... */
    {
        /* ... */
		GEngine->Tick(FApp::GetDeltaTime(), bIdleMode);
        /* ... */
    }
    /* ... */
}
```

### UGameEngine::Tick
[GameEngine.cpp](../UnrealEngine/Engine/Source/Runtime/Engine/Private/GameEngine.cpp)
```c++
void UGameEngine::Tick( float DeltaSeconds, bool bIdleMode )
{
    /* ... */
    for (int32 WorldIdx = 0; WorldIdx < WorldList.Num(); ++WorldIdx)
	{
		FWorldContext &Context = WorldList[WorldIdx];
		if (Context.World() == NULL || !Context.World()->ShouldTick())
		{
			continue;
		}

		GWorld = Context.World();

		// Tick all travel and Pending NetGames (Seamless, server, client)
		{
			QUICK_SCOPE_CYCLE_COUNTER(STAT_UGameEngine_Tick_TickWorldTravel);
			TickWorldTravel(Context, DeltaSeconds);
		}

		if (!bIdleMode)
		{
			SCOPE_TIME_GUARD(TEXT("UGameEngine::Tick - WorldTick"));

			// Tick the world.
			Context.World()->Tick( LEVELTICK_All, DeltaSeconds );
		}
        /* ... */
	}
    /* ... */
}
```

### UWorld::Tick
[LevelTick.cpp](../UnrealEngine/Engine/Source/Runtime/Engine/Private/LevelTick.cpp)
```c++
/**
 * Update the level after a variable amount of time, DeltaSeconds, has passed.
 * All child actors are ticked after their owners have been ticked.
 */
void UWorld::Tick( ELevelTick TickType, float DeltaSeconds )
{
    /* ... */
}
```

## World 的三种 Tick 机制
### 1. TimerManager

```c++
void UWorld::Tick( ELevelTick TickType, float DeltaSeconds )
{
    /* ... */
    if (TickType != LEVELTICK_TimeOnly && !bIsPaused)
    {
        SCOPE_TIME_GUARD_MS(TEXT("UWorld::Tick - TimerManager"), 5);
        STAT(FScopeCycleCounter Context(GetTimerManager().GetStatId());)
        GetTimerManager().Tick(DeltaSeconds);
    }
}
```

### 2. TickFunction

```c++
void UWorld::Tick( ELevelTick TickType, float DeltaSeconds )
{
    /* ... */
    RunTickGroup(TG_PrePhysics);
    RunTickGroup(TG_StartPhysics);
    RunTickGroup(TG_DuringPhysics, false);
    RunTickGroup(TG_EndPhysics);
    RunTickGroup(TG_PostPhysics);
    RunTickGroup(TG_PostUpdateWork);
    RunTickGroup(TG_LastDemotable);
}
```

```c++
/**
	* Run a tick group, ticking all actors and components
	* @param Group - Ticking group to run
	* @param bBlockTillComplete - if true, do not return until all ticks are complete
	*/
void UWorld::RunTickGroup(ETickingGroup Group, bool bBlockTillComplete = true)
{
	check(TickGroup == Group); // this should already be at the correct value, but we want to make sure things are happening in the right order
	FTickTaskManagerInterface::Get().RunTickGroup(Group, bBlockTillComplete);
	TickGroup = ETickingGroup(TickGroup + 1); // new actors go into the next tick group because this one is already gone
}
```

添加方式
```c++
/**
* Adds the tick function to the master list of tick functions.
* @param Level - level to place this tick function in
**/
void FTickFunction::RegisterTickFunction(ULevel* Level)
{
	if (!IsTickFunctionRegistered())
	{
		// Only allow registration of tick if we are are allowed on dedicated server, or we are not a dedicated server
		const UWorld* World = Level ? Level->GetWorld() : nullptr;
		if(bAllowTickOnDedicatedServer || !(World && World->IsNetMode(NM_DedicatedServer)))
		{
			if (InternalData == nullptr)
			{
				InternalData.Reset(new FInternalData());
			}
			FTickTaskManager::Get().AddTickFunction(Level, this);
			InternalData->bRegistered = true;
		}
	}
	else
	{
		check(FTickTaskManager::Get().HasTickFunction(Level, this));
	}
}
```

### 3. TickableGameObject

```c++
void UWorld::Tick( ELevelTick TickType, float DeltaSeconds )
{
    FTickableGameObject::TickObjects(this, TickType, bIsPaused, DeltaSeconds);
}
```

```c++
void FTickableGameObject::TickObjects(UWorld* World, const int32 InTickType, const bool bIsPaused, const float DeltaSeconds)
{
    for (const FTickableObjectEntry& TickableEntry : Statics.TickableObjects)
    {
        if (FTickableGameObject* TickableObject = static_cast<FTickableGameObject*>(TickableEntry.TickableObject))
			{
				// If it is tickable and in this world
				if (((TickableEntry.TickType == ETickableTickType::Always) || TickableObject->IsTickable()) 
					&& (TickableObject->GetTickableGameObjectWorld() == World)
					&& TickableObject->IsAllowedToTick())
				{
					const bool bIsGameWorld = InTickType == LEVELTICK_All || (World && World->IsGameWorld());
					// If we are in editor and it is editor tickable, always tick
					// If this is a game world then tick if we are not doing a time only (paused) update and we are not paused or the object is tickable when paused
					if ((GIsEditor && TickableObject->IsTickableInEditor()) ||
						(bIsGameWorld && ((!bIsPaused && TickType != LEVELTICK_TimeOnly) || (bIsPaused && TickableObject->IsTickableWhenPaused()))))
					{
						FScopeCycleCounter Context(TickableObject->GetStatId());
						TickableObject->Tick(DeltaSeconds);

						// In case it was removed during tick
						if (TickableEntry.TickableObject == nullptr)
						{
							bNeedsCleanup = true;
						}
					}
				}
			}
    }
}
```

## AActor Tick 的添加流程

```c++
void AActor::BeginPlay()
{
    /* ... */
	RegisterAllActorTickFunctions(true, false); // Components are done below.
    /* ... */
    for (UActorComponent* Component : Components)
	{
        /* ... */
        Component->RegisterAllComponentTickFunctions(true);
    }
}
```

```c++
void AActor::RegisterAllActorTickFunctions(bool bRegister, bool bDoComponents)
{
	if(!IsTemplate())
	{
		// Prevent repeated redundant attempts
		if (bTickFunctionsRegistered != bRegister)
		{
			FActorThreadContext& ThreadContext = FActorThreadContext::Get();
			check(ThreadContext.TestRegisterTickFunctions == nullptr);
			RegisterActorTickFunctions(bRegister);
			bTickFunctionsRegistered = bRegister;
			checkf(ThreadContext.TestRegisterTickFunctions == this, TEXT("Failed to route Actor RegisterTickFunctions (%s)"), *GetFullName());
			ThreadContext.TestRegisterTickFunctions = nullptr;
		}

		if (bDoComponents)
		{
			for (UActorComponent* Component : GetComponents())
			{
				if (Component)
				{
					Component->RegisterAllComponentTickFunctions(bRegister);
				}
			}
		}
	}
}
```

```c++
void AActor::RegisterActorTickFunctions(bool bRegister)
{
	check(!IsTemplate());

	if(bRegister)
	{
		if(PrimaryActorTick.bCanEverTick)
		{
			PrimaryActorTick.Target = this;
			PrimaryActorTick.SetTickFunctionEnable(PrimaryActorTick.bStartWithTickEnabled || PrimaryActorTick.IsTickFunctionEnabled());
			PrimaryActorTick.RegisterTickFunction(GetLevel());
		}
	}
	else
	{
		if(PrimaryActorTick.IsTickFunctionRegistered())
		{
			PrimaryActorTick.UnRegisterTickFunction();			
		}
	}

	FActorThreadContext::Get().TestRegisterTickFunctions = this; // we will verify the super call chain is intact. Don't copy and paste this to another actor class!
}
```

```c++
class ENGINE_API AActor : public UObject
{
    struct FActorTickFunction PrimaryActorTick;
}
```

```c++
struct FActorTickFunction : public FTickFunction
{
	GENERATED_USTRUCT_BODY()

	/**  AActor  that is the target of this tick **/
	class AActor*	Target;

	/** 
		* Abstract function actually execute the tick. 
		* @param DeltaTime - frame time to advance, in seconds
		* @param TickType - kind of tick for this frame
		* @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created
		* @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completetion of this task until certain child tasks are complete.
	**/
	ENGINE_API virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;
	/** Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph **/
	ENGINE_API virtual FString DiagnosticMessage() override;
	ENGINE_API virtual FName DiagnosticContext(bool bDetailed) override;
};
```