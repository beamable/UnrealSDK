// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_Operation.h"

#include "BeamK2.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_CallFunction.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_EnumEquality.h"
#include "K2Node_GetArrayItem.h"
#include "K2Node_SwitchEnum.h"
#include "K2Node_SwitchString.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Runtime/BeamRuntime.h"
using namespace BeamK2;

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation"

FName UK2BeamNode_Operation::GetSubsystemSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf);
}

FName UK2BeamNode_Operation::GetOperationFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginFrictionlessOperation);
}

void UK2BeamNode_Operation::BuildPinToolTipMap(TMap<FName, FString>& OutTooltipMap)
{
	OutTooltipMap.Add(OP_Operation_Handle, TEXT("A handle for this operation. You can use it as a dependency to WaitAll nodes."));

	OutTooltipMap.Add(OP_Operation_OnOperationEvent, TEXT("This flow will run whenever an operation event is triggered."));
	OutTooltipMap.Add(OP_Operation_UserSlots, TEXT("The user slot for the user performing this operation. Only relevant if developing a game with local multiplayer."));
	OutTooltipMap.Add(OP_Operation_Event, TEXT("The data for the raised operation event. Use this to understand what happened and react accordingly."));

	OutTooltipMap.Add(OP_Operation_Expanded_OnSuccess, TEXT("This flow only runs for events of type SUCCESS."));
	OutTooltipMap.Add(OP_Operation_Expanded_OnError, TEXT("This flow runs for events of type ERROR."));
	OutTooltipMap.Add(OP_Operation_Expanded_OnCancelled, TEXT("This flow runs for events of type CANCELLED."));

	TArray<FName> SuccessTypeSubEvents = GetOperationEventIds(OET_SUCCESS);
	TArray<FName> ErrorTypeSubEvents = GetOperationEventIds(OET_ERROR);
	TArray<FName> CancelledTypeSubEvents = GetOperationEventIds(OET_CANCELLED);

	TArray<FString> SuccessTypeSubEventTooltips = GetOperationEventIdTooltips(OET_SUCCESS);
	TArray<FString> ErrorTypeSubEventTooltips = GetOperationEventIdTooltips(OET_ERROR);
	TArray<FString> CancelledTypeSubEventTooltips = GetOperationEventIdTooltips(OET_CANCELLED);

	TArray<FName> AllEvents = {};
	for (FName Event : SuccessTypeSubEvents) AllEvents.AddUnique(Event);
	for (FName Event : ErrorTypeSubEvents) AllEvents.AddUnique(Event);
	for (FName Event : CancelledTypeSubEvents) AllEvents.AddUnique(Event);

	TArray<FString> AllEventTooltips = {};
	for (FString Event : SuccessTypeSubEventTooltips) AllEventTooltips.AddUnique(Event);
	for (FString Event : ErrorTypeSubEventTooltips) AllEventTooltips.AddUnique(Event);
	for (FString Event : CancelledTypeSubEventTooltips) AllEventTooltips.AddUnique(Event);

	for (int i = 0; i < AllEvents.Num(); ++i)
	{
		const auto SubEvent = AllEvents[i];
		const auto SubEventTooltip = AllEventTooltips[i];

		const auto SuccessExecPinName = SubEvent == NAME_None
			                                ? OP_Operation_Expanded_OnSuccess
			                                : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnSuccess.ToString(), *SubEvent.ToString()));
		const auto ErrorExecPinName = SubEvent == NAME_None ? OP_Operation_Expanded_OnError : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnError.ToString(), *SubEvent.ToString()));
		const auto CancelledExecPinName = SubEvent == NAME_None
			                                  ? OP_Operation_Expanded_OnCancelled
			                                  : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnCancelled.ToString(), *SubEvent.ToString()));

		OutTooltipMap.Add(SuccessExecPinName, TEXT("This flow will only run for this specific success case. If no case is specified, it'll run for the 'Operation Completed with Success' event."));
		OutTooltipMap.Add(ErrorExecPinName, TEXT("This flow will only run for this specific error case. If no case is specified, it'll run for the 'Operation Completed with Error' event."));
		OutTooltipMap.Add(CancelledExecPinName,
		                  TEXT("This flow will only run for this specific cancelled case. If no case is specified, it'll run for the 'Operation was Cancelled and Completed' event."));
	}
}

UClass* UK2BeamNode_Operation::GetRuntimeSubsystemClass() const
{
	return UBeamRuntime::StaticClass();
	//return UClass::StaticClass();
}

TMap<FName, UClass*> UK2BeamNode_Operation::GetOperationEventCastClass(EBeamOperationEventType Type) const
{
	return {
	};
}

TArray<FName> UK2BeamNode_Operation::GetOperationEventIds(EBeamOperationEventType Type) const
{
	return {
		NAME_None,
	};
}


TArray<FString> UK2BeamNode_Operation::GetOperationEventIdTooltips(EBeamOperationEventType Type) const
{
	return {
		FString::Printf(TEXT("The completion event for when this operation completes with %s."), *StaticEnum<EBeamOperationEventType>()->GetNameStringByValue(Type)),
	};
}

void UK2BeamNode_Operation::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto _ = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	const auto OperationFunction = GetRuntimeSubsystemClass()->FindFunctionByName(GetOperationFunctionName());
	bIsMultiUser = OperationFunction->HasMetaData(MD_BeamOperation_MultiUser);

	// Create the input pins for this ExecuteRequest node
	// Start by grabbing the request function, which give us the output pins of the graph this node hides as well as a couple of the input ones.	
	ParseFunctionForNodeInputPins(this, OperationFunction, WrappedOperationFunctionInputPinNames, IsIgnoredInputPinForExecuteRequestNode);

	// Create the output pins in an order that improves usability.
	EnforceOperationPins();
	if (bIsInBeamFlowMode)
	{
		EnforceBeamFlowModePins();
	}
	else
	{
		ParseFunctionForNodeInputPins(this, OperationFunction, {OP_Operation_OnOperationEvent}, true);
	}
}


void UK2BeamNode_Operation::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const auto ExpandModePropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_Operation, CurrentExpandedMode);
	if (PropertyChangedEvent.Property)
	{
		const auto CppName = PropertyChangedEvent.Property->GetNameCPP();
		const auto bChangedExpandedMode = CppName.Equals(ExpandModePropName.ToString());
		const auto bShouldRebuildPins = bChangedExpandedMode;
		if (bShouldRebuildPins)
		{
			if (bIsInBeamFlowMode)
				EnforceBeamFlowModePins();
			else
			{
				// TODO: Make the expanded mode work for non-beam flow mode too.
			}
		}
	}
}

void UK2BeamNode_Operation::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const UK2Node_CallFunction* CallGetSubsystem = CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	const UK2Node_CallFunction* CallRequestFunction = CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetOperationFunctionName(), GetRuntimeSubsystemClass());


	// Gets all relevant pins
	const auto ExecutionPin = K2Schema->FindExecutionPin(*this, EGPD_Input);
	if (ExecutionPin->LinkedTo.Num() > 1)
		CompilerContext.MessageLog.Error(TEXT("@@ has more than one input! Beam Flow nodes do not allow that!"), this);

	const auto ThenPin = K2Schema->FindExecutionPin(*this, EGPD_Output);
	const auto HandlePin = FindPin(OP_Operation_Handle);

	// Connects the result of the "static BeamApi::GetSelf" call to the "non-static RuntimeSubsystem::___Operation" Call Function node.
	SetUpPinsFunctionToOwnerSubsystem(CallGetSubsystem, CallRequestFunction);

	// Set up Input pins for the expanded operation node
	SetUpInputPinsForOperationNode(CompilerContext, CallRequestFunction, ExecutionPin);

	// Split out all the nodes for each "sub-graph": OnSuccess Sub-Graph, OnError Sub-Graph and OnComplete Sub-Graph. 
	if (bIsInBeamFlowMode)
	{
		// Expand the parts of the node that aren't shared.
		ExpandBeamFlowMode(CompilerContext, SourceGraph, CallRequestFunction, ThenPin);
	}
	else
	{
		// Expand the parts of the node that aren't shared.
		ExpandNonBeamFlowMode(CompilerContext, CallRequestFunction, ThenPin, HandlePin);
	}


	// This needs to exist so that the custom node is no longer in the graph and gets killed off when we cook the Blueprint.
	// This works because we fully replace and guarantee the execution flow is correctly set up.
	BreakAllNodeLinks();
}

UObject* UK2BeamNode_Operation::GetJumpTargetForDoubleClick() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetOperationFunctionName());

	if (!Function) return nullptr;

	FSourceCodeNavigation::NavigateToFunction(Function);

	return Super::GetJumpTargetForDoubleClick();
}

FName UK2BeamNode_Operation::GetCornerIcon() const
{
	return FName("BeamIcon_Operations");
}

void UK2BeamNode_Operation::EnterBeamFlowModeImpl()
{
	EnforceBeamFlowModePins();
}

void UK2BeamNode_Operation::ExitBeamFlowModeImpl()
{
	RemoveAllPins(this, {OP_Operation_OnOperationEvent, OP_Operation_UserSlots, OP_Operation_Event});
	const auto RequestFunction = GetRuntimeSubsystemClass()->FindFunctionByName(GetOperationFunctionName());
	ParseFunctionForNodeInputPins(this, RequestFunction, {OP_Operation_OnOperationEvent}, true);
}

bool UK2BeamNode_Operation::IsIgnoredInputPinForExecuteRequestNode(const UEdGraphNode* CustomNode, const FProperty* Param)
{
	// We ignore the OnComplete callback that will exist.
	const bool bIsResponseDelegate = Param->GetFName().ToString().StartsWith(TEXT("On"));

	// We ignore all Output parameters because we create these by hand.
	const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

	// We also ignore duplicated pin names. This is by design for now --- TODO: We need to resolve name collisions differently as this can easily hide bugs.
	const UEdGraphPin* EdGraphPin = CustomNode->FindPin(Param->GetFName());

	// Any of these are true, and the param doesn't become an input pin.
	return bIsResponseDelegate || bIsOutputParam || EdGraphPin;
}

void UK2BeamNode_Operation::EnforceOperationPins()
{
	const auto SynchronousFlowPin = EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then, TEXT(""));
	SynchronousFlowPin->PinFriendlyName = LOCTEXT("BeamNode", "Synchronous Flow");

	EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_Handle,
	                    TEXT("The Operation Handle to use with WaitAll nodes."), {}, FBeamOperationHandle::StaticStruct());
}


void UK2BeamNode_Operation::EnforceBeamFlowModePins()
{
	// Rebuild the tooltips
	PinTooltipMap.Reset();
	BuildPinToolTipMap(PinTooltipMap);

	FCreatePinParams Params;
	Params.ContainerType = bIsMultiUser ? EPinContainerType::Array : EPinContainerType::None;
	switch (CurrentExpandedMode.GetValue())
	{
	case OnCompleted:
		{
			// Remove all pins except the ones this mode cares about
			RemoveAllPinsExcept(this, [this](const UEdGraphNode*, const UEdGraphPin* Pin)
			{
				const TArray AllowedPins{
					UEdGraphSchema_K2::PN_Then,
					OP_Operation_Handle,
					OP_Operation_UserSlots,

					OP_Operation_OnOperationEvent,
					OP_Operation_Event
				};
				return Pin->Direction == EGPD_Input || AllowedPins.Contains(Pin->PinName);
			});

			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_OnOperationEvent, PinTooltipMap[OP_Operation_OnOperationEvent]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_Event, PinTooltipMap[OP_Operation_Event], {}, FBeamOperationEvent::StaticStruct());
			break;
		}
	case Success_Error_Cancelled:
		{
			// Remove all pins except the ones this mode cares about
			RemoveAllPinsExcept(this, [this](const UEdGraphNode*, const UEdGraphPin* Pin)
			{
				const TArray AllowedPins{

					UEdGraphSchema_K2::PN_Then,
					OP_Operation_Handle,
					OP_Operation_UserSlots,
					OP_Operation_Expanded_OnSuccess,
					OP_Operation_Expanded_OnError,
					OP_Operation_Expanded_OnCancelled,
					OP_Operation_Event,
				};
				return Pin->Direction == EGPD_Input || AllowedPins.Contains(Pin->PinName);
			});

			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnSuccess, PinTooltipMap[OP_Operation_Expanded_OnSuccess]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnError, PinTooltipMap[OP_Operation_Expanded_OnError]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnCancelled, PinTooltipMap[OP_Operation_Expanded_OnCancelled]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_Event, PinTooltipMap[OP_Operation_Event], {}, FBeamOperationEvent::StaticStruct());
			break;
		}
	case OnSubEvents:
		{
			TArray<FName> PinsToKeep
			{
				UEdGraphSchema_K2::PN_Then,
				OP_Operation_Handle,
				OP_Operation_UserSlots
			};

			// Get the sub-events that are related to each higher event type.			
			TArray<FName> SuccessTypeSubEvents = GetOperationEventIds(OET_SUCCESS);
			TArray<FName> ErrorTypeSubEvents = GetOperationEventIds(OET_ERROR);
			TArray<FName> CancelledTypeSubEvents = GetOperationEventIds(OET_CANCELLED);

			TMap<FName, UClass*> SuccessCastClass = GetOperationEventCastClass(OET_SUCCESS);
			TMap<FName, UClass*> ErrorCastClass = GetOperationEventCastClass(OET_ERROR);
			TMap<FName, UClass*> CancelledCastClass = GetOperationEventCastClass(OET_CANCELLED);

			const auto EnforceRelevantEventPins = [this](const TArray<FName>& AvailableSubEvents, const FName& BaseExecPinName, int& AddedCount, TArray<FName>& CreatedFlowPins, TMap<FName, UClass*> CastClasses)
			{
				for (int i = 0; i < AvailableSubEvents.Num(); ++i)
				{
					const auto& SubEvent = AvailableSubEvents[i];
					const auto& SubEventName = SubEvent.ToString();

					// If we have the event name as default, we just name it as the regular operation. Otherwise we name it  
					const auto ExecPinName = SubEvent == NAME_None ? BaseExecPinName : FName(FString::Printf(TEXT("%s - %s"), *BaseExecPinName.ToString(), *SubEventName));
					const auto ExecPinTooltip = PinTooltipMap[ExecPinName];
					CreatedFlowPins.Add(ExecPinName);
					EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, ExecPinName, ExecPinTooltip);


					if (CastClasses.Contains(SubEvent))
					{
						EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Object, CastClasses[SubEvent]->GetFName(), ExecPinTooltip, {}, CastClasses[SubEvent]);
					}

					AddedCount += 1;
				}
			};

			for (auto CastClassToKeep : SuccessCastClass)
			{
				PinsToKeep.Add(CastClassToKeep.Value->GetFName());
			}

			for (auto CastClassToKeep : ErrorCastClass)
			{
				PinsToKeep.Add(CastClassToKeep.Value->GetFName());
			}

			for (auto CastClassToKeep : CancelledCastClass)
			{
				PinsToKeep.Add(CastClassToKeep.Value->GetFName());
			}

			// Enforce the sub events for each type are added in order.
			auto RelevantEventsAdded = 0;
			SuccessEventFlowPinNames.Empty();
			EnforceRelevantEventPins(SuccessTypeSubEvents, OP_Operation_Expanded_OnSuccess, RelevantEventsAdded, SuccessEventFlowPinNames, SuccessCastClass);
			for (int i = 0; i < SuccessEventFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(SuccessEventFlowPinNames[i]);
			}


			// Set up the UserSlot pins after the on success
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());

			ErrorEventFlowPinNames.Empty();
			EnforceRelevantEventPins(ErrorTypeSubEvents, OP_Operation_Expanded_OnError, RelevantEventsAdded, ErrorEventFlowPinNames, ErrorCastClass);
			for (int i = 0; i < ErrorEventFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(ErrorEventFlowPinNames[i]);
			}

			CancelledEventFlowPinNames.Empty();
			EnforceRelevantEventPins(CancelledTypeSubEvents, OP_Operation_Expanded_OnCancelled, RelevantEventsAdded, CancelledEventFlowPinNames, CancelledCastClass);
			for (int i = 0; i < CancelledEventFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(CancelledEventFlowPinNames[i]);
			}

			// We always expose the Event Data --- this is the entire `FBeamOperationEvent` struct and is valid in all flows here.
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_Event, PinTooltipMap[OP_Operation_Event], {}, FBeamOperationEvent::StaticStruct());
			PinsToKeep.Add(OP_Operation_Event);

			// Remove all pins except the ones this mode cares about
			RemoveAllPinsExcept(this, [this, PinsToKeep](const UEdGraphNode*, const UEdGraphPin* Pin)
			{
				return Pin->Direction == EGPD_Input || PinsToKeep.Contains(Pin->PinName);
			});
			break;
		}
	default: break;
	}

	GetGraph()->NotifyGraphChanged();
}


void UK2BeamNode_Operation::ExpandBeamFlowMode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin* const ThenPin)
{
	switch (CurrentExpandedMode.GetValue())
	{
	case OnCompleted:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			UEdGraphPin* UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.
			const auto CompleteFlowPin = FindPin(OP_Operation_OnOperationEvent);
			const auto ResultPin = FindPin(OP_Operation_Event);


			const TArray<UEdGraphPin*> StartingGraphs{ThenPin, CompleteFlowPin,};
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.			
			ValidateOutputPinUsage(CompilerContext, {UserSlotsPin, ResultPin}, {Operation_UserSlotsPinInSynchronousFlowMessage, Operation_ResultPinInSynchronousFlowMessage},
			                       OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForOnCompleteBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, OutPerFlowNodes[1], OutPerFlowEventNodes[1],
			                               CompleteFlowPin, ResultPin, UserSlotsPin);
			break;
		}
	case Success_Error_Cancelled:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			const auto UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.
			const auto SuccessFlowPin = FindPin(OP_Operation_Expanded_OnSuccess);
			const auto ErrorFlowPin = FindPin(OP_Operation_Expanded_OnError);
			const auto CancelledFlowPin = FindPin(OP_Operation_Expanded_OnCancelled);
			const auto EventDataPin = FindPin(OP_Operation_Event);

			const TArray<UEdGraphPin*> StartingGraphs{ThenPin, SuccessFlowPin, ErrorFlowPin, CancelledFlowPin};
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.
			ValidateOutputPinUsage(CompilerContext,
			                       {UserSlotsPin, EventDataPin},
			                       {Operation_ResultPinInSynchronousFlowMessage, Operation_UserSlotsPinInSynchronousFlowMessage, Operation_DataPinInSynchronousFlowMessage},
			                       OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForSuccessErrorCancelledBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, SuccessFlowPin,
			                                          UserSlotsPin, ErrorFlowPin, EventDataPin, CancelledFlowPin, OutPerFlowNodes,
			                                          OutPerFlowEventNodes);

			break;
		}
	case OnSubEvents:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			const auto UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.

			const auto EventPin = FindPin(OP_Operation_Event);

			TArray<UEdGraphPin*> StartingGraphs{ThenPin,};
			for (const auto& Pin : SuccessEventFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			for (const auto& Pin : ErrorEventFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			for (const auto& Pin : CancelledEventFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};

			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.
			TArray<UEdGraphPin*> InvalidSynchronousFlowPins = {UserSlotsPin,};
			if (EventPin) InvalidSynchronousFlowPins.Add(EventPin);
			TArray<FString> InvalidSynchronousFlowPinsValidationErrors = {Operation_UserSlotsPinInSynchronousFlowMessage,};
			if (EventPin) InvalidSynchronousFlowPinsValidationErrors.Add(Operation_DataPinInSynchronousFlowMessage);
			ValidateOutputPinUsage(CompilerContext, InvalidSynchronousFlowPins, InvalidSynchronousFlowPinsValidationErrors, OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForSubEventsBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, EventPin, OutPerFlowNodes, OutPerFlowEventNodes);
			break;
		}
	default: break;
	}
}

void UK2BeamNode_Operation::ExpandNonBeamFlowMode(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin* const ThenPin, UEdGraphPin* const HandlePin)
{
	const TArray<UEdGraphPin*> StartingGraphs{ThenPin,};
	TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
	TArray<TArray<UEdGraphNode*>> OutPerEventFlowNodes;
	GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, {}, OutPerFlowNodes, OutPerEventFlowNodes);

	// Move the connected delegate pins over to the Call Request Function		
	MoveWrappedPin(this, CompilerContext, CallOperationFunction, OP_Operation_OnOperationEvent);

	// Make sure all output pins in this node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
	SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerEventFlowNodes[0], CallOperationFunction, ThenPin, HandlePin);
}


void UK2BeamNode_Operation::SetUpInputPinsForOperationNode(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin* ExecutionPin)
{
	// Get the execution pin from the CallRequest node
	const auto CallRequestFunctionExecPin = CallOperationFunction->FindPinChecked(UEdGraphSchema_K2::PN_Execute);

	// Moves the execution flow from the default "Then" execution pin of this custom node to the "Then" Exec pin of the "____ Request" CallFunction node.	
	const auto MovedRegularExecutionFlow = CompilerContext.MovePinLinksToIntermediate(*ExecutionPin, *CallRequestFunctionExecPin);
	check(!MovedRegularExecutionFlow.IsFatal())

	// Finally, we move all the rest of the parameters into 
	for (const auto& WrappedFunctionPin : WrappedOperationFunctionInputPinNames)
	{
		if (const auto FunctionPin = CallOperationFunction->FindPin(WrappedFunctionPin))
		{
			const auto Pin = this->FindPin(WrappedFunctionPin);
			UE_LOG(LogTemp, Verbose, TEXT("Looking at Request Function Pin %s, %d"), *FunctionPin->PinName.ToString(), WrappedOperationFunctionInputPinNames.Num())

			// We should not be doing this more than once for each input pin --- if we do that's a critical BUG: and we need to sort out why and fix it.
			// The BUG is that the latter connection would override the first one. 
			checkf(!FunctionPin->HasAnyConnections(), TEXT("PinName=%s"), *FunctionPin->PinName.ToString())
			CompilerContext.MovePinLinksToIntermediate(*Pin, *FunctionPin);
		}
	}
}

void UK2BeamNode_Operation::SetUpPinsForSynchronousFlow(FKismetCompilerContext& CompilerContext, const TArray<UEdGraphNode*>& SyncFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
                                                        const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin* ThenPin, UEdGraphPin* HandlePin)
{
	// Moves the operation handle pin.
	const auto CallOperationReturnPin = CallOperationFunction->GetReturnValuePin();
	const auto Moved = CompilerContext.MovePinLinksToIntermediate(*HandlePin, *CallOperationReturnPin);
	check(!Moved.IsFatal());

	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> CustomNodePins{HandlePin};
	const TArray<UEdGraphPin*> IntermediatePins{CallOperationReturnPin};
	ReplaceConnectionsOnBeamFlow(SyncFlowNodes, CustomNodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, CustomNodePins, IntermediatePins);

	const auto CallRequestThenPin = CallOperationFunction->GetThenPin();
	// -- Tie the flow of the CallFunction Then pin (Output Execution pin) to the node which the Synchronous Flow pin is connected.
	const auto MovedRegularThenFlow = CompilerContext.MovePinLinksToIntermediate(*ThenPin, *CallRequestThenPin);
	check(!MovedRegularThenFlow.IsFatal())
}

void UK2BeamNode_Operation::SetUpPinsForOnCompleteBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
                                                           const TArray<UEdGraphNode*>& CompleteFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes, UEdGraphPin* CompletePin,
                                                           UEdGraphPin* ResultPin, UEdGraphPin* UserSlotsPin)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the CompleteEventNode and set up the OnComplete Flow
	const UK2Node_Event* IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));

	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);
	const auto IntermediateEventExecPin = IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
	const auto IntermediateEventDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto IntermediateEventResultPin = IntermediateEventNode->FindPinChecked(OP_Operation_Event);


	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> CompletePins{ResultPin};
	const TArray<UEdGraphPin*> CompleteEventPins{IntermediateEventResultPin};
	ReplaceConnectionsOnBeamFlow(CompleteFlowNodes, CompletePins, CompleteEventPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, CompletePins, CompleteEventPins);

	// Move the execution flow from the "On Complete" pin to the "Then" execution pin of the CompleteEvent node.  
	const auto ExecFlowMoved = CompilerContext.MovePinLinksToIntermediate(*CompletePin, *IntermediateEventExecPin);
	check(!ExecFlowMoved.IsFatal());
	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateEventDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_Operation::SetUpPinsForSuccessNotSuccessBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
                                                                  UEdGraphPin* const SuccessFlowPin, UEdGraphPin* const UserSlotsPin, UEdGraphPin* const OthersFlowPin,
                                                                  TArray<TArray<UEdGraphNode*>> OutPerFlowNodes, TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the Delegate Pin
	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);

	// Create the IntermediateEventNode and get its pins
	const UK2Node_Event* IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));

	// FBeamOperationCompleteHandler(const TArray<FUserSlot>& UserSlots, FBeamOperationResult OperationResult);
	const auto BreakStructNode = CreateBreakStructNode(this, CompilerContext, SourceGraph, K2Schema, FBeamOperationEvent::StaticStruct(),
	                                                   IntermediateEventNode->FindPinChecked(OP_Operation_Event));

	// Create the node that will check if the result code was success or not
	const auto EnumEquality = CreateEnumEqualityAgainstDefault(this, CompilerContext, SourceGraph, K2Schema,
	                                                           StaticEnum<EBeamOperationEventType>(), static_cast<uint8>(EBeamOperationEventType::OET_SUCCESS),
	                                                           BreakStructNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventType)));

	// Connect the EnumEquality to the Condition pin and the Then pin
	const auto* IfThenElseNode = CreateIfThenElseNodeAgainstCondition(this, CompilerContext, SourceGraph, K2Schema,
	                                                                  IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then),
	                                                                  EnumEquality->GetReturnValuePin());

	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> NodePins{};
	const TArray<UEdGraphPin*> IntermediatePins{};
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[1], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes[1], NodePins, IntermediatePins);

	// Does the same for all nodes and pins in the others flow.
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[2], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes[2], NodePins, IntermediatePins);

	// Move the execution flow from the "On Success" pin to the "Then" execution pin of the CompleteEvent node.
	ConnectIfThenElseNodeOutputs(CompilerContext, SuccessFlowPin, OthersFlowPin, IfThenElseNode);

	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto IntermediateDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}


void UK2BeamNode_Operation::SetUpPinsForSuccessErrorCancelledBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
                                                                      UEdGraphPin* const SuccessFlowPin, UEdGraphPin* const UserSlotsPin,
                                                                      UEdGraphPin* const ErrorFlowPin, UEdGraphPin* const EventDataPin, UEdGraphPin* const CancelledFlowPin,
                                                                      TArray<TArray<UEdGraphNode*>> OutPerFlowNodes,
                                                                      TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the Delegate Pin
	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);
	// Create the IntermediateEventNode and get its pins
	const auto IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));

	// Break the result struct out into its components
	const auto IntermediateOperationEventNode = IntermediateEventNode->FindPinChecked(OP_Operation_Event);
	const auto BreakOperationResultNode = CreateBreakStructNode(this, CompilerContext, SourceGraph, K2Schema, FBeamOperationEvent::StaticStruct(), IntermediateOperationEventNode);

	// Switch on the result code for the operation
	const auto SwitchEnum = CreateSwitchEnumNode(this, CompilerContext, SourceGraph, K2Schema, StaticEnum<EBeamOperationEventType>(),
	                                             IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then),
	                                             BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventType)));


	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> NodePins{EventDataPin};
	const TArray<UEdGraphPin*> IntermediatePins{IntermediateOperationEventNode};
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[1], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes[1], NodePins, IntermediatePins);
	// Does the same for all nodes and pins in the others flow.
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[2], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes[2], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[3], NodePins, IntermediatePins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes[3], NodePins, IntermediatePins);

	// Move the execution flow from the Custom Node's flow pins to the intermediate ones
	{
		// Get the flow pins
		const auto IntermediateSuccessFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(EBeamOperationEventType::OET_SUCCESS));
		const auto IntermediateErrorFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(EBeamOperationEventType::OET_ERROR));
		const auto IntermediateCancelledFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(EBeamOperationEventType::OET_CANCELLED));

		const auto SuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*SuccessFlowPin, *IntermediateSuccessFlowPin);
		check(!SuccessFlowMoved.IsFatal());

		const auto ErrorFlowMoved = CompilerContext.MovePinLinksToIntermediate(*ErrorFlowPin, *IntermediateErrorFlowPin);
		check(!ErrorFlowMoved.IsFatal());

		const auto CancelledFlowMoved = CompilerContext.MovePinLinksToIntermediate(*CancelledFlowPin, *IntermediateCancelledFlowPin);
		check(!CancelledFlowMoved.IsFatal());
	}

	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto IntermediateDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_Operation::SetUpPinsForSubEventsBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
                                                          UEdGraphPin* const EventStructPin, const TArray<TArray<UEdGraphNode*>>& PerFlowNodes, const TArray<TArray<UEdGraphNode*>>& PerFlowEventNodes)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the Delegate Pin
	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);
	// Create the IntermediateEventNode and get its pins
	const auto IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));

	// Break the result struct out into its components
	const auto OperationEventPin = IntermediateEventNode->FindPinChecked(OP_Operation_Event);
	const auto BreakOperationResultNode = CreateBreakStructNode(this, CompilerContext, SourceGraph, K2Schema, FBeamOperationEvent::StaticStruct(), OperationEventPin);

	// Switch on the result code for the operation
	const auto SwitchEnum = CreateSwitchEnumNode(this, CompilerContext, SourceGraph, K2Schema, StaticEnum<EBeamOperationEventType>(),
	                                             IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then),
	                                             BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventType)));

	// Expand the Success SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, GetOperationEventIds(OET_SUCCESS), GetOperationEventCastClass(OET_SUCCESS), SuccessEventFlowPinNames, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(OET_SUCCESS)));

	// Expand the Error SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, GetOperationEventIds(OET_ERROR), GetOperationEventCastClass(OET_ERROR), ErrorEventFlowPinNames, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(OET_ERROR)));


	// Expand the Cancelled SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, GetOperationEventIds(OET_CANCELLED), GetOperationEventCastClass(OET_CANCELLED), CancelledEventFlowPinNames, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(OET_CANCELLED)));

	for (int i = 0; i < PerFlowNodes.Num(); ++i)
	{
		// Replace the connections of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
		const TArray<UEdGraphPin*> NodePins{EventStructPin};
		const TArray<UEdGraphPin*> IntermediatePins{OperationEventPin};

		const auto Flow = PerFlowNodes[i];
		const auto EventFlow = PerFlowEventNodes[i];
		ReplaceConnectionsOnBeamFlow(Flow, NodePins, IntermediatePins);
		ReplaceConnectionsOnBeamFlow(EventFlow, NodePins, IntermediatePins);
	}

	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto IntermediateDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_Operation::ExpandBeamFlowSubEvents(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
                                                    const TArray<FName>& EventIds, const TMap<FName, UClass*>& EventDataCasts, const TArray<FName>& EventsFlowPinNames,
                                                    UK2Node_BreakStruct* const BreakOperationResultNode, UEdGraphPin* const SubEventSwitchExecPin)
{
	const auto SubTypeCodePin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventId));

	// Switch on it out of the EventIds pin of the EventType switch	
	const auto SubEventSwitch = CreateSwitchNameNode(this, CompilerContext, SourceGraph, K2Schema, EventIds, SubEventSwitchExecPin, SubTypeCodePin);
	for (int i = 0; i < EventsFlowPinNames.Num(); ++i)
	{
		const auto FlowPin = FindPin(EventsFlowPinNames[i]);

		
		// Get the intermediate pins we'll need to connect to all the places our custom node's output pins are connected to.
		// If we expect a string, than we forward the raw event data string. Otherwise...
		const auto SubEventValue = EventIds[i];
		auto IntermediateSubEventFlowPin = SubEventSwitch->FindPin(SubEventValue);

		// Create the cast node and link the success and fail to the subevent execute
		if (EventDataCasts.Contains(SubEventValue))
		{
			auto EventDataPin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventData));
			auto CastedOutputPin = FindPin(EventDataCasts[SubEventValue]->GetName());

			auto CastNode = CreateDynamicCastNode(this, CompilerContext, SourceGraph, EventDataCasts[SubEventValue]);
			
			K2Schema->TryCreateConnection(CastNode->GetCastSourcePin(), EventDataPin);

			K2Schema->TryCreateConnection(CastNode->GetExecPin(), IntermediateSubEventFlowPin);
			
			const auto SuccessFlowCastObject =CompilerContext.MovePinLinksToIntermediate(*CastedOutputPin, *CastNode->GetCastResultPin());
			check(!SuccessFlowCastObject.IsFatal());

			const auto SuccessFlowMovedCastSuccess = CompilerContext.MovePinLinksToIntermediate(*FlowPin, *CastNode->GetValidCastPin());
			check(!SuccessFlowMovedCastSuccess.IsFatal());

			const auto SuccessFlowMovedCastFail = CompilerContext.MovePinLinksToIntermediate(*FlowPin, *CastNode->GetInvalidCastPin());
			check(!SuccessFlowMovedCastFail.IsFatal());
		}
		else
		{
			// Get the flow pins
			const auto SuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*FlowPin, *IntermediateSubEventFlowPin);
			check(!SuccessFlowMoved.IsFatal());
		}
	}
}

#undef LOCTEXT_NAMESPACE
