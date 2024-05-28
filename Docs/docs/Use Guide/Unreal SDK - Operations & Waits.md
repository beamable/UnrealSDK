<style>
img[src*='#center'] { 
    display: block;
    margin: auto;
}
</style>
# Unreal SDK - Operations & Waits

The Beamable SDK uses slight variation on Promises we named Operations. These provide the same semantics as promises but their implementation is slightly different to allow for a BP-compatible API.

They wrap concurrent *operations* (mostly HTTP Requests) under a `FBeamOperationHandle` exposed to some higher-level system. To put it in simpler terms:

> When you want to expose a single function that makes a bunch of requests and emits events as responses come in, ultimately handling success/failure of the entire sequence, use an Operation.

We provide a lot of Operations inside our `UBeamRuntimeSubsystem` implementations; covering most basic use-cases. However, understanding how to create your own operations enables you to add behavior to last-mile hooks we expose. A couple of examples:

- "I want to go talk to a microservice to fetch additional data for a user before you trigger the `OnBeamableReady` callback."
- "I want to go talk to a microservice to validate that you can actually join this matchmaking queue."

!!! warning
	While possible, we don't recommend creating the actual operations as blueprints. Its OK to do so for a quick experimentation session; but shipping with it is *not recommended*. **Calling *Operations* that are written in C++ is the primary way we recommend Blueprints to interact with the Beamable SDK (we even have special nodes for it).** 
## Operation Lifecycle

Every Operation has an `int64` id called the `FBeamOperationHandle`. We use it to track the operation's state, its emitted events, its current status and which of Beamable's requests are part of it, so on and so forth...

The lifecycle of an operation goes as follows:

1. Create it with calls to `[CPP_]BeginOperation` passing in an `FBeamOperationEventHandler[Code]`.
	1. The event handler is called whenever any event of any type is triggered; the `FBeamOperationEvent` struct has data in it useful for deciding how to respond to the event.
2. Its status stays as `ONGOING` until `UBeamRequestTracker`'s `TriggerOperationSuccess`, `TriggerOperationError` or `TriggerOperationCancelled` functions are called with the created `FBeamOperationHandle` and, optionally, some `FString` data.
	1. While its `ONGOING`, you can make calls to `TriggerOperationEvent` passing in any `SubEvent` other than `NAME_None`. This triggers an event that will call the Operation's `FBeamOperationEventHandler[Code]` but will not change its status.
	2. `TriggerOperationSuccess`, `TriggerOperationError` and `TriggerOperationCancelled` are just wrappers around `TriggerOperationEvent` with a `SubEvent == NAME_None`.
3. Once a final event (any event with `SubEvent == NAME_None`) is triggered, the Operation is completed and its `FBeamOperationEventHandler[Code]` runs a final time.
4. The Operation is not cleaned up while other Operations or Waits (see `[CPP_]WaitAll`) depend on it.
	1. Every now and again we clean them up in a tick functions with low tick rate (check `UBeamRequestTracker` for more information).
## Writing and Exposing your Own Operations
We try and expose all of our main SDK operations in both BP and CPP flavors. If you'd like to do the same thing, this section is for you. If you're looking for how to write hooks in C++, look into the next section.

The primary trade-off is that: BP-Compatible versions do not allow for lambda binding and variable capturing. The CPP Version does allow for those things and, as they can be extremely useful for development speed and other cases, we decided on supporting both flavors.

The snippet below explains how to write an operation for both BP and CPP; sharing its actual logic. 

```c++
// This is the BP-Compatible Function
FBeamOperationHandle U________::__________Operation(FUserSlot UserSlot, (...OperationParams...), FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)  
{  
	// First, we start an operation using the BP-Compatible BeginOperation call
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);  

	// Then, we call a function that takes in the operation parameters and the Handle for the operation.
	TheActualOperationLogic(UserSlot, (...OperationParams...), Handle);  

	// Operation functions usually return the handle so that callers can ask questions about the state of the operation if they want to.	
	return Handle;  
}  

// This is the CPP Function
FBeamOperationHandle U__________::CPP_________Operation(FUserSlot UserSlot, (...OperationParams...), FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)  
{  
	// First, we start an operation using the BP-Compatible BeginOperation call
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);  
	
	// Then, we call a function that takes in the operation parameters and the Handle for the operation.
	TheActualOperationLogic(UserSlot, Key, Value, Handle);  

	// Operation functions usually return the handle so that callers can ask questions to UBeamRequestTracker about the state of the operation if they want to.	
	return Handle; 
}


void U__________::TheActualOperationLogic(FUserSlot Slot, (...OperationParams...), FBeamOperationHandle Op)  
{  
	// This is mostly an example snippet of things you can do...

	// We can check the local client state and fail operations without any request ever being made.
    // For example, check if a user is authenticated or not.
    FBeamRealmUser RealmUser;  
    if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))  
    {       
	RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));  
	return;  
    }  
    
    // We can also prepare a request handler, capturing the "Op" Handle
    const auto SomeRequestHandler = FOn______::CreateLambda([this, Op](F______ Resp)  
    {  

		// If the request is being retried, we don't do anything.
		// But... we could go update a UI here or something...
		if (Resp.State == RS_Retrying) return;
		
		// If the request was successful, we can trigger the Operation as a success.
		if (Resp.State == RS_Success)  
		{
			// (...) change local system's state	        
			RequestTracker->TriggerOperationSuccess(Op, {});  
		}
		// If the request failed, we can trigger the Operation as a success.
		else 
		{ 
			// (...) handle error and trigger the Operation as an error.
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error); 
		}
	});    
	
	// Make the request passing in the "Op" Handle (this tracks lets our UBeamBackend know not to clean up the request until the Operation has finished)
	auto Ctx = Request____(Slot, (...ReqParams...), Op, SomeRequestHandler);
}
```

!!! warning Parameter Names and Beam Flow
	The parameter names `UserSlot`, `OnOperationEvent` and `CallingContext` are important! They allow you to write your own implementation of our Beam Flow node for your operation. Look at the [Beam Flow Nodes](#beam-flow-nodes-operations) section for more information on how to create these.

There are ton of examples of operations in our SDK. For some guidance, you can take a look at any of our various runtime subsystems such as:

- `UBeamStatsSubsystem`
- `UBeamInventorySubsystem`
- `UBeamLobbySubsystem`
- Any other sub-class of `UBeamRuntimeSubsystem`.

Feel free to copy-paste them as a template of how to implement and reason about `Operations`.
### Beam Flow Nodes - Operations

Beam-Flow nodes are the purple nodes with Beamable Icons that you can find. There are two flavors of them; one are Raw Requests that you can use to hit our APIs; the other is the Operation Beam Flow node.

![beam-flow-node](./Images/Unreal_Operations_And_Waits_BeamFlowNodes.png#center)

Beamable Operation Flow Nodes assume a few things:

- There's some number of participating `UserSlots` .
- There's an event handler that'll handle the three types of events: `OET_SUCCESS`, `OET_ERROR` and `OET_CANCELLED`.
- There's some `FString` data associated with each of those events.

To create these nodes for your own operations, you can look at any of our own nodes (that live inside our `UncookedOnly` module: `BeamableCoreBlueprintNodes` ) and copy/paste one implementation changing the values accordingly. 

Restrictions on exposing `UFUNCTIONs` with these nodes:

- The function must be declared from inside a `UGameInstanceSubsystem` / `UBeamRuntimeSubsystem` subclass.
- The function must be a `UFUNCTION` that returns a `FBeamOperationHandle`.
- The signature must contain the following named parameters:
	- `FUserSlot UserSlot`, if a single user is involved in the operation, or `TArray<FUserSlot> UserSlot`, if multiple users are involved in the operation.
	- If multiple users, the `UFUNCTION` must also add `meta=(BeamOperationMultiUser)`.
	- `FBeamOperationEventHandler OnOperationEvent` to be the event handler that will handle all events raised by the operation.
- The function can have any other parameters you want in any order as long as the above parameters are there.

Here's an example of what you need to declare one of these.

```c++
#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitInventoryUpdate"  
  
UCLASS(meta=(BeamFlowNode))  
class UK2BeamNode_Operation_CommitInventoryUpdate : public UK2BeamNode_Operation  
{  
    GENERATED_BODY()  

	// This returns the title of the node.
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Inventory - CommitInventoryUpdate"); }  

	// This should get a static UFUNCTION that returns a valid instance of the UGameInstanceSubsystem containing the Operation function.
    virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }  

	// This should return the UFUNCTION Operation's name.
    virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, CommitInventoryUpdateOperation); }  

	// This should get the UGameInstanceSubsystem class
    virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }  
  
};  
  
#undef LOCTEXT_NAMESPACE
```

As long as you have one of these in an `UncookedOnly` module of your application, you should be able to expose your own operations as BP nodes (this is compatible with Multiplayer PIE mode).
## Writing Hooks...
... and other `FBeamOperationHandle` returning functions. These are the various callback flavors that we expose so you can customize your experience with our SDK. In other words:

> If you ever see a Delegate or Virtual Function that you can implement that returns one or more `FBeamOperationHandle`, you need to create operations and return their handles so that we can wait on your code before we proceed with ours.

Here are the flavors:

1. **Delayed Operation**: Its basically a simple parameterless callback that returns a `FBeamOperationHandle` our SDK should wait for.
	1. See our various `UBeamRuntime::LoginGuest` functions for an example on how to use these in your own code.
2. **Runtime Subsystem Implementation**: Implementations of virtual functions in one of our SDK's base classes such as `UBeamRuntimeSubsystem`.
	1. This is for when you wish to make a system that ties into the Beamable life-cycle like our own systems do.
	2. This is rarely needed, but... in custom enough use-cases, its likely to be the best way to accomplish your goals.
3. **Hooks:**  Hook into one of the various  `DEFINE_BEAM_OPERATION_HOOK` hooks.
	1. We don't use Hooks ourselves IN ANY CIRCUNSTANCES and leave these as "game-maker-only extensions".
	2. You can search for `DEFINE_BEAM_OPERATION_HOOK` and find some usages of the macro to better understand these. 

### Beam Operation Hooks
**Hooks** have some more context that you should know about how to use them:

1. You call some Operation we expose in our SDK. That Operation does a bunch of things and triggers the hooks at some well-known point during their execution.
	1. Since you have the source code, you can look into these functions and see the exact semantics of the trigger but we do try and keep these documented in call-site comments.
2. Triggering the hooks mean:
	1. The returned `FBeamOperationHandles` from the hooks are fed into  `UBeamRequestTracker::WaitAll`.
	2. Our operation will wait for all your hooks to complete; successfully or otherwise.
	3. If your registered operations fail, we'll log out the errors that exist inside that operation and let you know clearly the problem happened in the operation you provided to the hook.
	4. If your operations succeeded, we'll continue with our own operation and eventually trigger that as a success.
	5. The semantics of what happens in case of a failure change from hook to hook, but... for the most part, we'll fail our own operation if any hooks fail.

Here's a "template example" of how this stuff will typically look like:

```C++
// Let's say you want to run some synchronous code at a hook but don't really want to make any request to anything.
// In that case you can get the system and add a hook that:
const U_____ SomeSystem;  
SomeSystem->Hook.Add(F____::CreateLambda([this]()  
{  
	// (...) Does some synchronous code
	// This means that your operation is completed at the end of this function
	
	// For cases like these, we provide the utility function below.
	// This creates and immediately completes an operation and returns its handle.
    return GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginSuccessfulOperation({}, FString("MySystemName"), FString(""), FBeamOperationEventHandlerCode{});  
}));  

// Let's say you want to call some microservice you wrote as part of our operation
// In that case you can add a hook that:
SomeSystem->Hook.Add(F____::CreateLambda([this]()  
{  
	// Begins an operation
    const auto Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, FString("MySystemName"), {});

	// Get Microservice Subsystem that exposes calls to it
    const auto MyMsApi = GEngine->GetEngineSubsystem<UMyMsApi>();  
    const auto MyMsReq = UMyMsRequest::Make(GetTransientPackage(), {});  
	
	// Create the handler for the request capturing the "Op" its a part of.
    const auto MyMsHandler = FOnMyMsFullResponse::CreateLambda([this, Op](FMyMsFullResponse Resp)  
    {       
		// If we timedout and are retrying the request, do nothing.
		if(Resp.State == RS_Retrying)  
			return;			
		
	    UE_LOG(LogTemp, Display, TEXT("Talked to a Microservice from a Hook!!!! Look at that, huh?"));  
	
		// If the response from the Microservice was not a success, fail the operation.
		if(Resp.State != RS_Success)  
		{	
			// Trigger the operation as a success
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, Resp.ErrorData.message);  
			return;  
		}  
		
		// (...) Do stuff with the Microservice's response
		
		// Trigger the operation as a success
       GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, FString(""));  
    });   

	// Make the request
	FBeamRequestContext Ctx;  
    MyMsApi->CPP_MyMs(UserSlot, MyMsReq, MyMsHandler, Ctx, Op, GetGameInstance());  

	// Return the create Operation
    return Op;  
}));
```

## Why not Promises?

The biggest reason not to do that is Blueprint Compatibility. The most recognizable template-based Promise-style API just won't work with BPs. As such, we wanted to create a underlying system that was a superset of that style of API but that retained BP compatibility even if it lost the template-based interface.

The result was this Operation system.

!!! info
	In using it inside our own SDK to develop our Stateful `UBeamRuntimeSubsystems`, we found that we didn't miss the template aspect or its chaining aspect of `Do().Then()`. However, the chaining might be something we eventually look into. Perhaps adding the ability to chain requests like these as "syntactic sugar"; but its highly unlikely we'll do anything with templates at the Operation-layer as we do not want to lose the BP-Compatibility.




