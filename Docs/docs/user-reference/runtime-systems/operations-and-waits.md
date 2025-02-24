# Unreal SDK - Operations & Waits
The Beamable SDK uses slight variation on Promises we named Operations. 
These provide the same semantics as promises but their implementation is slightly different to allow for a BP-compatible API.

They wrap concurrent *operations* (mostly HTTP Requests) under a `FBeamOperationHandle` exposed to some higher-level system.
To put it in simpler terms:

> When you want to expose a single function that makes a bunch of requests and emits events as responses come in, ultimately handling success/failure of the entire sequence, use an Operation.

We provide a lot of Operations inside our `UBeamRuntimeSubsystem` implementations; covering most basic use-cases.
However, understanding how to create your own operations enables you to add behavior to last-mile hooks we expose. A couple of examples:

- "I want to go talk to a microservice to fetch additional data for a user before the SDK's `UBeamRuntime::OnUserReady` callback."
- "I want to go talk to a microservice to validate that you can actually join this matchmaking queue."

!!! warning
	While possible, we don't recommend creating the actual operations as blueprints. 
    It's OK to do so for a quick experimentation session; but shipping with it is *not recommended*.
    **Calling *Operations* that are written in C++ is the primary way we recommend Blueprints to interact with the Beamable SDK (we even have special nodes for it).**

## Operation Lifecycle

Every Operation has an `int64` id called the `FBeamOperationHandle`. 
We use it to track the operation's state, its emitted events, its current status and which of Beamable's requests are part of it.

The lifecycle of an operation goes as follows:

![operation-and-waits-lifecycle.png](../../media/imgs/operation-and-waits-lifecycle.png)

## Writing and Exposing your Own Operations
We try and expose all of our main SDK operations in both BP and CPP flavors. 
If you'd like to do the same thing, this section is for you. If you're looking for how to write hooks in C++, look into the next section.

The primary trade-off is that: 

- BP-Compatible versions do not allow for lambda binding and variable capturing. 
- The CPP Version does allow for those things and, as they can be extremely useful for development speed and other cases, we decided on supporting both flavors.

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
	The parameter names `UserSlot`, `OnOperationEvent` and `CallingContext` are important! 
    They allow you to write your own implementation of our Beam Flow node for your operation. 
    Look at the [Beam Flow Nodes](#beam-flow-nodes-operations) section for more information on how to create these.

There are tons of examples of operations in our SDK. For some guidance, you can take a look at any of our various runtime subsystems such as:

- `UBeamStatsSubsystem`
- `UBeamInventorySubsystem`
- `UBeamLobbySubsystem`
- Any other sub-class of `UBeamRuntimeSubsystem`.

Feel free to copy-paste them as a template of how to implement and reason about `Operations`.

### Beam Flow Nodes - Operations
There are two flavors of Beam-Flow nodes; one are Raw Requests that you can use to hit our APIs; the other is the Operation Beam Flow node.
Operation Nodes look like this:

![beam-flow-node](../../media/imgs/operation-and-waits-beam-flow-nodes.png)

Beamable Operation Flow Nodes assume a few things:

- One or more participating `UserSlots` (see [User Slots](user-slots.md) for more information).
- An event handler for handling any of the events.
- Events can be: `OET_SUCCESS`, `OET_ERROR` and `OET_CANCELLED` plus a `FName EventCode`.     
- Events can contain some arbitrary data associated with them (implementations of `IBeamOperationEventData`).

To create these nodes for your own operations, you can look at any of our own nodes (that live inside our `UncookedOnly` module: `BeamableCoreBlueprintNodes` ) and copy/paste one implementation changing the values accordingly.
However, there are a few restrictions:

- The function must be a `UFUNCTION` that returns a `FBeamOperationHandle` and contains the following named parameters:
	- `FUserSlot UserSlot`, if a single user is involved in the operation, or `TArray<FUserSlot> UserSlot`, if multiple users are involved in the operation.
      - If multiple users, the `UFUNCTION` must also add `meta=(BeamOperationMultiUser)`.
	- `FBeamOperationEventHandler OnOperationEvent` to be the event handler that will handle all events raised by the operation.
    - The function can have any other parameters you want in any order as long as the above parameters are there.
- The function must be declared from inside a `UGameInstanceSubsystem` / `UBeamRuntimeSubsystem` subclass.

Here's an example of what you need to declare one of these (we recommend copying from your own SDK code instead of this snippet).

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
... and other `FBeamOperationHandle` returning functions. 
These are the various callback flavors that we expose so you can customize your experience with our SDK. In other words:

> If you ever see a Delegate or Virtual Function that you can implement that returns one or more `FBeamOperationHandle`, you need to create operations and return their handles so that we can wait on your code before we proceed with ours.
> It's basically a way for you to inject a promise that we'll run as part of a larger process.

There are a few flavors of this around the SDK:

1. **Delayed Operation**: It's basically a simple parameter-less callback that returns a `FBeamOperationHandle` our SDK should wait for.
	1. See our `UBeamRuntime::LoginGuest` function for an example of this.
2. **Runtime Subsystem Implementation**: Implementations of virtual functions in one of our SDK's base classes such as `UBeamRuntimeSubsystem`.
	1. This is for when you wish to make a system that ties into the Beamable life-cycle like our own `UBeamRuntimeSubsystem` implementations do.
	2. This is rarely needed, but... in unique custom use-cases, it's likely to be the best way to accomplish your goals.
3. **Hooks:** Bind into delegates created via `DEFINE_BEAM_OPERATION_HOOK`.
	1. We don't use Hooks ourselves IN ANY CIRCUNSTANCES and leave these as "game-maker-only extensions".
	2. You can search for `DEFINE_BEAM_OPERATION_HOOK` and find some usages of the macro to better understand these. 

### Beam Operation Hooks
**Hooks** have some more context that you should know about how to use them:

1. You call some Operation we expose in our SDK. That Operation does a bunch of things and triggers the hooks at some well-known point during their execution.
	1. Since you have the source code, you can look into these functions and see the exact semantics of the trigger, but we do try and keep these documented in call-site comments.
2. Whenever a set of hooks are triggered, what we are actually doing is:
	1. The returned `FBeamOperationHandles` from the hooks are fed into a `UBeamRequestTracker::WaitAll` call.
	2. Our operation will wait for all your hooks to complete; successfully or otherwise.
	3. If your registered operations fail, we'll log out the errors that exist inside those operations and let you know clearly the problem happened in the operation you provided to the hook.
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

## Why not Template-based Promises?
The biggest reason not to do that is Blueprint Compatibility. The most recognizable template-based Promise-style API just won't work with BPs.
As such, we wanted to create an underlying system that provided the same functionality but that retained BP compatibility even if it lost the template-based interface.
The result was this Operation system.

!!! info
	In using it inside our own SDK to develop our Stateful `UBeamRuntimeSubsystems`, we found that we didn't miss the template aspect or its chaining aspect of `Do().Then()`.
    However, the chaining might be something we eventually look into. Perhaps adding the ability to chain requests like these as "syntactic sugar"; but its highly unlikely we'll do anything with templates at the Operation-layer as we do not want to lose the BP-Compatibility.

## Waits
This is equivalent to `Promise.All` or `Task.WhenAll` keeping with our promise analogy. It can be used to wait on a set of operations and/or requests executed concurrently whose errors and successes are handled all at once. 
To use this, call `UBeamRequestTracker::[CPP_]WaitAll`.

This function takes arrays of `FBeamRequestContext`, `FBeamOperationHandle` and/or `FBeamWaitHandle` and a handler function.
It'll wait until all the provided handles are completed and then gather all emitted events and request responses and invoke your handle function passing in a helper struct to identify successes/failures.

You can find examples of these in our SDKs so you can learn how to use this yourself. The most common examples are:

- `UBeamRuntime`'s Initialization and Login's Lifecycle is defined as a multi-step operation with several wait points.
- `UBeamContentSubsystem` also has an example around how we fetch content updates.

---

Understanding these concepts and how to leverage them can unlock the maximum potential uses and customizability of the SDK; but superficial knowledge is sufficient for the most basic use-cases. 
Take your time and refer back to this page as you need!



