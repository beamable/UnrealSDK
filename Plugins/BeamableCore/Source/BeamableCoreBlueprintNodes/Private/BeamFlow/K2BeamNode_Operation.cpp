// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_Operation.h"

#include "BeamK2.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_CallFunction.h"
#include "K2Node_EnumEquality.h"
#include "K2Node_GetArrayItem.h"
#include "K2Node_SwitchEnum.h"
#include "KismetCompiler.h"
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

	OutTooltipMap.Add(OP_Operation_Expanded_RequestId, TEXT("If the event happened as a consequence of a request, this will be that Request's Id. Otherwise, it'll be -1."));
	OutTooltipMap.Add(OP_Operation_Expanded_SuccessData, TEXT("The success data embeded into the event."));
	OutTooltipMap.Add(OP_Operation_Expanded_ErrorData, TEXT("The error data embeded into the event."));
	OutTooltipMap.Add(OP_Operation_Expanded_CancelledData, TEXT("The cancelled data embeded into the event."));
	OutTooltipMap.Add(OP_Operation_Expanded_Data, TEXT("The data embeded into the event."));

	OutTooltipMap.Add(OP_Operation_Expanded_OnSuccess, TEXT("This flow only runs for events of type SUCCESS."));
	OutTooltipMap.Add(OP_Operation_Expanded_OnOthers, TEXT("This flow runs for all events that don't have specific flows for them. Think of it as a 'default' case in the switch statement."));
	OutTooltipMap.Add(OP_Operation_Expanded_OnError, TEXT("This flow runs for events of type ERROR."));
	OutTooltipMap.Add(OP_Operation_Expanded_OnCancelled, TEXT("This flow runs for events of type CANCELLED."));

	const auto Enum = GetOperationSubTypeEnum();
	TArray<FString> SuccessTypeSubEvents;
	TArray<FString> ErrorTypeSubEvents;
	TArray<FString> CancelledTypeSubEvents;
	GatherSubEventsFromSubTypeEnum(Enum, SuccessTypeSubEvents, ErrorTypeSubEvents, CancelledTypeSubEvents);

	for (int i = 0; i < Enum->NumEnums(); ++i)
	{
		const auto SubEvent = Enum->GetNameStringByIndex(i);
		const auto SubEventValue = Enum->GetValueByIndex(i);

		const auto SuccessExecPinName = SubEventValue == 0 ? OP_Operation_Expanded_OnSuccess : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnSuccess.ToString(), *SubEvent));
		const auto ErrorExecPinName = SubEventValue == 0 ? OP_Operation_Expanded_OnError : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnError.ToString(), *SubEvent));
		const auto CancelledExecPinName = SubEventValue == 0 ? OP_Operation_Expanded_OnCancelled : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_OnCancelled.ToString(), *SubEvent));

		const auto SuccessDataPinName = SubEventValue == 0 ? OP_Operation_Expanded_SuccessData : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_SuccessData.ToString(), *SubEvent));
		const auto ErrorDataPinName = SubEventValue == 0 ? OP_Operation_Expanded_ErrorData : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_ErrorData.ToString(), *SubEvent));
		const auto CancelledDataPinName = SubEventValue == 0
			                                  ? OP_Operation_Expanded_CancelledData
			                                  : FName(FString::Printf(TEXT("%s - %s"), *OP_Operation_Expanded_CancelledData.ToString(), *SubEvent));

		OutTooltipMap.Add(SuccessExecPinName, TEXT("This flow will only run for this specific success case. If no case is specified, it'll run for the 'Operation Completed with Success' event."));
		OutTooltipMap.Add(ErrorExecPinName, TEXT("This flow will only run for this specific error case. If no case is specified, it'll run for the 'Operation Completed with Error' event."));
		OutTooltipMap.Add(CancelledExecPinName,
		                  TEXT("This flow will only run for this specific cancelled case. If no case is specified, it'll run for the 'Operation was Cancelled and Completed' event."));

		OutTooltipMap.Add(SuccessDataPinName, FString::Printf(TEXT("This data is available only for the flow for the 'Success - %s'  case."), *SubEvent));
		OutTooltipMap.Add(ErrorDataPinName, FString::Printf(TEXT("This data is available only for the flow for the 'Error - %s'  case."), *SubEvent));
		OutTooltipMap.Add(CancelledDataPinName, FString::Printf(TEXT("This data is available only for the flow for the 'Cancelled - %s'  case."), *SubEvent));
	}


	OutTooltipMap.Add(OP_Operation_Expanded_OnCancelled, TEXT("This flow runs for events of type CANCELLED."));
}

UClass* UK2BeamNode_Operation::GetRuntimeSubsystemClass() const
{
	return UBeamRuntime::StaticClass();
	//return UClass::StaticClass();
}

UEnum* UK2BeamNode_Operation::GetOperationSubTypeEnum() const
{
	return StaticEnum<EDefaultOperationEventSubType>();
}

TMap<uint8, UScriptStruct*> UK2BeamNode_Operation::GetOperationSubTypeUStructs() const
{
	TMap<uint8, UScriptStruct*> SubEventToDataType;
	SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
	SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(1), nullptr);
	SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(2), nullptr);
	SubEventToDataType.Add(static_cast<EDefaultOperationEventSubType>(3), nullptr);
	return SubEventToDataType;
}

TMap<uint8, UClass*> UK2BeamNode_Operation::GetOperationSubTypeConversionFunctionClass() const
{
	TMap<uint8, UClass*> SubEventToConversionClass;
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), nullptr);
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(1), nullptr);
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(2), nullptr);
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(3), nullptr);
	return SubEventToConversionClass;
}

TMap<uint8, FName> UK2BeamNode_Operation::GetOperationSubTypeConversionFunctionName() const
{
	// Use this macro to point to the conversion function and map it to the sub-event type.
	// GET_FUNCTION_NAME_CHECKED_OneParam(USubTypeConversionFunctionClass, ConversionFunction, FString))	
	TMap<uint8, FName> SubEventToConversionClass;
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(0), TEXT(""));
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(1), TEXT(""));
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(2), TEXT(""));
	SubEventToConversionClass.Add(static_cast<EDefaultOperationEventSubType>(3), TEXT(""));
	return SubEventToConversionClass;
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
	const auto SuccessSubEventsPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_Operation, RelevantSuccessSubEvents);
	const auto ErrorSubEventsPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_Operation, RelevantErrorSubEvents);
	const auto CancelledSubEventsPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_Operation, RelevantCancelledSubEvents);
	if (PropertyChangedEvent.Property)
	{
		const auto CppName = PropertyChangedEvent.Property->GetNameCPP();
		const auto bChangedExpandedMode = CppName.Equals(ExpandModePropName.ToString());
		const auto bRelevantSubEvent = CurrentExpandedMode == OnSubEvents && (
			CppName.Equals(SuccessSubEventsPropName.ToString()) ||
			CppName.Equals(ErrorSubEventsPropName.ToString()) ||
			CppName.Equals(CancelledSubEventsPropName.ToString())
		);

		const auto bShouldRebuildPins = bChangedExpandedMode || bRelevantSubEvent;
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

					OP_Operation_OnOperationEvent,
					OP_Operation_UserSlots,
					OP_Operation_Event
				};
				return Pin->Direction == EGPD_Input || AllowedPins.Contains(Pin->PinName);
			});

			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_OnOperationEvent, PinTooltipMap[OP_Operation_OnOperationEvent]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots,
			                    PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_Event, PinTooltipMap[OP_Operation_Event], {}, FBeamOperationEvent::StaticStruct());
			break;
		}
	case Success_NonSuccess:
		{
			// Remove all pins except the ones this mode cares about
			RemoveAllPinsExcept(this, [this](const UEdGraphNode*, const UEdGraphPin* Pin)
			{
				const TArray AllowedPins{
					UEdGraphSchema_K2::PN_Then,
					OP_Operation_Handle,
					OP_Operation_Expanded_OnSuccess,
					OP_Operation_Expanded_RequestId,
					OP_Operation_UserSlots,
					OP_Operation_Expanded_OnOthers
				};
				return Pin->Direction == EGPD_Input || AllowedPins.Contains(Pin->PinName);
			});

			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnSuccess, PinTooltipMap[OP_Operation_Expanded_OnSuccess]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Int64, OP_Operation_Expanded_RequestId, PinTooltipMap[OP_Operation_Expanded_RequestId]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnOthers, PinTooltipMap[OP_Operation_Expanded_OnOthers]);
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
					OP_Operation_Expanded_OnSuccess,
					OP_Operation_Expanded_RequestId,
					OP_Operation_UserSlots,
					OP_Operation_Expanded_OnError,
					OP_Operation_Expanded_ErrorData,
					OP_Operation_Expanded_OnCancelled
				};
				return Pin->Direction == EGPD_Input || AllowedPins.Contains(Pin->PinName);
			});

			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnSuccess, PinTooltipMap[OP_Operation_Expanded_OnSuccess]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Int64, OP_Operation_Expanded_RequestId, PinTooltipMap[OP_Operation_Expanded_RequestId]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnError, PinTooltipMap[OP_Operation_Expanded_OnError]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_String, OP_Operation_Expanded_ErrorData, PinTooltipMap[OP_Operation_Expanded_ErrorData]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnCancelled, PinTooltipMap[OP_Operation_Expanded_OnCancelled]);
			break;
		}
	case OnSubEvents:
		{
			TArray<FName> PinsToKeep
			{
				UEdGraphSchema_K2::PN_Then,
				OP_Operation_Handle,
				OP_Operation_Expanded_RequestId,
				OP_Operation_UserSlots
			};

			// Get the sub-events that are related to each higher event type.
			const auto Enum = GetOperationSubTypeEnum();
			const auto MappedTypes = GetOperationSubTypeUStructs();
			TArray<FString> SuccessTypeSubEvents;
			TArray<FString> ErrorTypeSubEvents;
			TArray<FString> CancelledTypeSubEvents;
			GatherSubEventsFromSubTypeEnum(Enum, SuccessTypeSubEvents, ErrorTypeSubEvents, CancelledTypeSubEvents);

			const auto EnforceRelevantEventPins = [this](const UEnum* Enum, const TMap<uint8, UScriptStruct*>& MappedTypes, const TArray<FString>& AvailableSubEvents,
			                                             const TArray<uint8>& RelevantSubEvents, const FName& BaseExecPinName, const FName& BaseDataPinName,
			                                             int& AddedCount, TArray<FName>& CreatedFlowPins, TArray<FName>& CreatedDataPins, TArray<uint8>& NotRelevantSubEvents)
			{
				for (const auto& SubEvent : AvailableSubEvents)
				{
					const auto SubEventValue = static_cast<uint8>(Enum->GetValueByNameString(SubEvent));
					if (!RelevantSubEvents.Contains(SubEventValue))
					{
						NotRelevantSubEvents.Add(SubEventValue);
						continue;
					}

					const auto StructType = MappedTypes.FindChecked(SubEventValue);

					// All Operation specific enums must have their first name as "Final" and a value of 0.
					// Also, we don't support custom data structures for the Final callbacks. We could do it, but semantically it'd require us to support it across all modes and
					// that is a bit harder than it's worth it.
					// Since all event structures MUST have a conversion from string (JSON) implemented with the default USTRUCT json conversion, a single cast-node covers this edge case.				
					if (SubEventValue == 0)
					{
						check(SubEvent.Equals(GET_ENUMERATOR_NAME_CHECKED(EDefaultOperationEventSubType, Final).ToString()));
						check(!StructType)
					}

					// If we have the event name as default, we just name it as the regular operation. Otherwise we name it  
					const auto ExecPinName = SubEventValue == 0 ? BaseExecPinName : FName(FString::Printf(TEXT("%s - %s"), *BaseExecPinName.ToString(), *SubEvent));
					const auto ExecPinTooltip = PinTooltipMap[ExecPinName];
					CreatedFlowPins.Add(ExecPinName);
					EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, ExecPinName, ExecPinTooltip);


					// We'll forward the message and system pins of the default error along
					const auto DataPinName = SubEventValue == 0 ? BaseDataPinName : FName(FString::Printf(TEXT("%s - %s"), *BaseDataPinName.ToString(), *SubEvent));
					const auto DataPinTooltip = PinTooltipMap[DataPinName];
					CreatedDataPins.Add(DataPinName);
					if (StructType)
						EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, DataPinName, DataPinTooltip, {}, StructType);
					else
						EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_String, DataPinName, DataPinTooltip);

					AddedCount += 1;
				}
			};

			// Enforce the sub events for each type are added in order.
			auto RelevantEventsAdded = 0;
			SuccessSubEventsFlowPinNames.Empty();
			SuccessSubEventsDataPinNames.Empty();
			SuccessSubEventsNotRelevantValues.Empty();
			EnforceRelevantEventPins(Enum, MappedTypes, SuccessTypeSubEvents, RelevantSuccessSubEvents, OP_Operation_Expanded_OnSuccess, OP_Operation_Expanded_SuccessData,
			                         RelevantEventsAdded, SuccessSubEventsFlowPinNames, SuccessSubEventsDataPinNames, SuccessSubEventsNotRelevantValues);
			for (int i = 0; i < SuccessSubEventsFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(SuccessSubEventsFlowPinNames[i]);
				PinsToKeep.Add(SuccessSubEventsDataPinNames[i]);
			}


			// Set up the RequestId and UserSlot pins after the on success 
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Int64, OP_Operation_Expanded_RequestId, PinTooltipMap[OP_Operation_Expanded_RequestId]);
			EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Struct, OP_Operation_UserSlots, PinTooltipMap[OP_Operation_UserSlots], Params, FUserSlot::StaticStruct());

			ErrorSubEventsFlowPinNames.Empty();
			ErrorSubEventsDataPinNames.Empty();
			ErrorSubEventsNotRelevantValues.Empty();
			EnforceRelevantEventPins(Enum, MappedTypes, ErrorTypeSubEvents, RelevantErrorSubEvents, OP_Operation_Expanded_OnError, OP_Operation_Expanded_ErrorData,
			                         RelevantEventsAdded, ErrorSubEventsFlowPinNames, ErrorSubEventsDataPinNames, ErrorSubEventsNotRelevantValues);
			for (int i = 0; i < ErrorSubEventsFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(ErrorSubEventsFlowPinNames[i]);
				PinsToKeep.Add(ErrorSubEventsDataPinNames[i]);
			}

			CancelledSubEventsFlowPinNames.Empty();
			CancelledSubEventsDataPinNames.Empty();
			CancelledSubEventsNotRelevantValues.Empty();
			EnforceRelevantEventPins(Enum, MappedTypes, CancelledTypeSubEvents, RelevantCancelledSubEvents, OP_Operation_Expanded_OnCancelled, OP_Operation_Expanded_CancelledData,
			                         RelevantEventsAdded, CancelledSubEventsFlowPinNames, CancelledSubEventsDataPinNames, CancelledSubEventsNotRelevantValues);
			for (int i = 0; i < CancelledSubEventsFlowPinNames.Num(); ++i)
			{
				PinsToKeep.Add(CancelledSubEventsFlowPinNames[i]);
				PinsToKeep.Add(CancelledSubEventsDataPinNames[i]);
			}

			// If we are not handling all errors, we have a catch all that takes in the raw EventData string as it's parameter pin.
			if (RelevantEventsAdded < SuccessTypeSubEvents.Num() + ErrorTypeSubEvents.Num() + CancelledTypeSubEvents.Num())
			{
				EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_Operation_Expanded_OnOthers, PinTooltipMap[OP_Operation_Expanded_OnOthers]);
				PinsToKeep.Add(OP_Operation_Expanded_OnOthers);

				EnforcePinExistence(this, EGPD_Output, UEdGraphSchema_K2::PC_String, OP_Operation_Expanded_Data, PinTooltipMap[OP_Operation_Expanded_Data]);
				PinsToKeep.Add(OP_Operation_Expanded_Data);
			}

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
			const auto CompleteFlowPin = FindPin(OP_Operation_OnOperationEvent);
			const auto ResultPin = FindPin(OP_Operation_Event);
			UEdGraphPin* UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.

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
	case Success_NonSuccess:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			const auto SuccessFlowPin = FindPin(OP_Operation_Expanded_OnSuccess);
			const auto RequestIdPin = FindPin(OP_Operation_Expanded_RequestId);
			const auto UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.
			const auto OthersFlowPin = FindPin(OP_Operation_Expanded_OnOthers);

			const TArray<UEdGraphPin*> StartingGraphs{ThenPin, SuccessFlowPin, OthersFlowPin};
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.
			ValidateOutputPinUsage(CompilerContext, {RequestIdPin, UserSlotsPin}, {Operation_ResultPinInSynchronousFlowMessage, Operation_UserSlotsPinInSynchronousFlowMessage},
			                       OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForSuccessNotSuccessBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, SuccessFlowPin, RequestIdPin, UserSlotsPin, OthersFlowPin, OutPerFlowNodes,
			                                      OutPerFlowEventNodes);
			break;
		}
	case Success_Error_Cancelled:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			const auto SuccessFlowPin = FindPin(OP_Operation_Expanded_OnSuccess);
			const auto RequestIdPin = FindPin(OP_Operation_Expanded_RequestId);
			const auto UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.
			const auto ErrorFlowPin = FindPin(OP_Operation_Expanded_OnError);
			const auto ErrorMessagePin = FindPin(OP_Operation_Expanded_ErrorData);
			const auto CancelledFlowPin = FindPin(OP_Operation_Expanded_OnCancelled);

			const TArray<UEdGraphPin*> StartingGraphs{ThenPin, SuccessFlowPin, ErrorFlowPin, CancelledFlowPin};
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.
			ValidateOutputPinUsage(CompilerContext,
			                       {RequestIdPin, UserSlotsPin, ErrorMessagePin},
			                       {Operation_ResultPinInSynchronousFlowMessage, Operation_UserSlotsPinInSynchronousFlowMessage, Operation_ErrorPinInSynchronousFlowMessage},
			                       OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForSuccessErrorCancelledBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, SuccessFlowPin, RequestIdPin, UserSlotsPin, ErrorFlowPin, ErrorMessagePin, OutPerFlowNodes,
			                                          OutPerFlowEventNodes);

			break;
		}
	case OnSubEvents:
		{
			// Gets the relevant pins
			const auto HandlePin = FindPin(OP_Operation_Handle);
			const auto RequestIdPin = FindPin(OP_Operation_Expanded_RequestId);
			const auto UserSlotsPin = FindPin(OP_Operation_UserSlots); // This can be either an array pin or a single pin --- depends on whether or not this operation involves multiple users.
			const auto OthersFlowPin = FindPin(OP_Operation_Expanded_OnOthers);
			const auto OthersDataPin = FindPin(OP_Operation_Expanded_Data);

			const int NumSubEvents = SuccessSubEventsDataPinNames.Num() + ErrorSubEventsDataPinNames.Num() + CancelledSubEventsDataPinNames.Num();

			TArray<UEdGraphPin*> StartingGraphs{ThenPin,};
			if (OthersFlowPin) StartingGraphs.Add(OthersFlowPin);
			for (const auto& Pin : SuccessSubEventsFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			for (const auto& Pin : ErrorSubEventsFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			for (const auto& Pin : CancelledSubEventsFlowPinNames) StartingGraphs.Add(FindPin(Pin));
			const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};

			TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
			TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
			GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

			// Validate that the Synchronous Flow does not use Pins that are not available for them.
			TArray<UEdGraphPin*> InvalidSynchronousFlowPins = {RequestIdPin, UserSlotsPin,};
			if (OthersDataPin) StartingGraphs.Add(OthersDataPin);
			for (const auto& Pin : SuccessSubEventsDataPinNames) InvalidSynchronousFlowPins.Add(FindPin(Pin));
			for (const auto& Pin : ErrorSubEventsDataPinNames) InvalidSynchronousFlowPins.Add(FindPin(Pin));
			for (const auto& Pin : CancelledSubEventsDataPinNames) InvalidSynchronousFlowPins.Add(FindPin(Pin));

			TArray<FString> InvalidSynchronousFlowPinsValidationErrors = {Operation_ResultPinInSynchronousFlowMessage, Operation_UserSlotsPinInSynchronousFlowMessage};
			if (OthersDataPin) InvalidSynchronousFlowPinsValidationErrors.Add(Operation_DataPinInSynchronousFlowMessage);
			for (int i = 0; i < NumSubEvents; ++i) InvalidSynchronousFlowPinsValidationErrors.Add(Operation_DataPinInSynchronousFlowMessage);
			ValidateOutputPinUsage(CompilerContext, InvalidSynchronousFlowPins, InvalidSynchronousFlowPinsValidationErrors, OutPerFlowNodes[0]);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
			SetUpPinsForSynchronousFlow(CompilerContext, OutPerFlowNodes[0], OutPerFlowEventNodes[0], CallOperationFunction, ThenPin, HandlePin);

			// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
			SetUpPinsForSubEventsBeamFlow(CompilerContext, SourceGraph, CallOperationFunction, RequestIdPin, UserSlotsPin, OthersFlowPin, OthersDataPin, OutPerFlowNodes, OutPerFlowEventNodes);
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
	for (const auto WrappedFunctionPin : WrappedOperationFunctionInputPinNames)
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
	// If this is not a multi-user operation, we get the Slot at Idx0 and forward it along to the pin.
	const auto IntermediateUserSlotPin = ExpandIntoArrayOrRegularIntermediatePin(this, CompilerContext, SourceGraph, IntermediateEventNode, OP_Operation_UserSlots,
	                                                                             bIsMultiUser);

	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> CompletePins{ResultPin, UserSlotsPin};
	const TArray<UEdGraphPin*> CompleteEventPins{IntermediateEventResultPin, IntermediateUserSlotPin};
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
                                                                  UEdGraphPin* const SuccessFlowPin, UEdGraphPin* const RequestIdPin, UEdGraphPin* const UserSlotsPin, UEdGraphPin* const OthersFlowPin,
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

	// Get the intermediate pins we'll need to connect to all the places our custom node's output pins are connected to.	
	const auto BreakRequestIdPin = BreakStructNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, RequestId));
	const auto IntermediateUserSlotPin = ExpandIntoArrayOrRegularIntermediatePin(this, CompilerContext, SourceGraph, IntermediateEventNode, OP_Operation_UserSlots, bIsMultiUser);

	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> NodePins{RequestIdPin, UserSlotsPin};
	const TArray<UEdGraphPin*> IntermediatePins{BreakRequestIdPin, IntermediateUserSlotPin};
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
                                                                      UEdGraphPin* const SuccessFlowPin, UEdGraphPin* const RequestIdPin, UEdGraphPin* const UserSlotsPin,
                                                                      UEdGraphPin* const ErrorFlowPin, UEdGraphPin* const ErrorDataPin, TArray<TArray<UEdGraphNode*>> OutPerFlowNodes,
                                                                      TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the Delegate Pin
	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);
	// Create the IntermediateEventNode and get its pins
	const auto IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));

	// Break the result struct out into its components
	const auto BreakOperationResultNode = CreateBreakStructNode(this, CompilerContext, SourceGraph, K2Schema, FBeamOperationEvent::StaticStruct(),
	                                                            IntermediateEventNode->FindPinChecked(OP_Operation_Event));

	// Switch on the result code for the operation
	const auto SwitchEnum = CreateSwitchEnumNode(this, CompilerContext, SourceGraph, K2Schema, StaticEnum<EBeamOperationEventType>(),
	                                             IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then),
	                                             BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventType)));


	// Get the intermediate pins we'll need to connect to all the places our custom node's output pins are connected to.
	const auto IntermediateErrorMessagePin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventData));
	const auto IntermediateRequestIdPin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, RequestId));
	const auto IntermediateUserSlotPin = ExpandIntoArrayOrRegularIntermediatePin(this, CompilerContext, SourceGraph, IntermediateEventNode, OP_Operation_UserSlots, bIsMultiUser);
	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> NodePins{RequestIdPin, UserSlotsPin, ErrorDataPin};
	const TArray<UEdGraphPin*> IntermediatePins{IntermediateRequestIdPin, IntermediateUserSlotPin, IntermediateErrorMessagePin};
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
		const auto IntermediateSuccessFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_SUCCESS)));
		const auto IntermediateErrorFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_ERROR)));
		const auto IntermediateCancelledFlowPin = SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_CANCELLED)));

		const auto SuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*SuccessFlowPin, *IntermediateSuccessFlowPin);
		check(!SuccessFlowMoved.IsFatal());

		const auto ErrorFlowMoved = CompilerContext.MovePinLinksToIntermediate(*ErrorFlowPin, *IntermediateErrorFlowPin);
		check(!ErrorFlowMoved.IsFatal());

		const auto CancelledFlowMoved = CompilerContext.MovePinLinksToIntermediate(*SuccessFlowPin, *IntermediateCancelledFlowPin);
		check(!CancelledFlowMoved.IsFatal());
	}

	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto IntermediateDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_Operation::SetUpPinsForSubEventsBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
                                                          UEdGraphPin* const RequestIdPin, UEdGraphPin* const UserSlotsPin, UEdGraphPin* const OthersFlowPin, UEdGraphPin* const OthersDataPin,
                                                          TArray<TArray<UEdGraphNode*>> OutPerFlowNodes, TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the Delegate Pin
	const auto OnCompleteDelegatePin = CallOperationFunction->FindPinChecked(OP_Operation_OnOperationEvent, EGPD_Input);
	// Create the IntermediateEventNode and get its pins
	const auto IntermediateEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("BeamOperationEventHandler"));
	const auto IntermediateUserSlotPin = ExpandIntoArrayOrRegularIntermediatePin(this, CompilerContext, SourceGraph, IntermediateEventNode, OP_Operation_UserSlots, bIsMultiUser);

	// Break the result struct out into its components
	const auto BreakOperationResultNode = CreateBreakStructNode(this, CompilerContext, SourceGraph, K2Schema, FBeamOperationEvent::StaticStruct(),
	                                                            IntermediateEventNode->FindPinChecked(OP_Operation_Event));

	// Switch on the result code for the operation
	const auto SwitchEnum = CreateSwitchEnumNode(this, CompilerContext, SourceGraph, K2Schema, StaticEnum<EBeamOperationEventType>(),
	                                             IntermediateEventNode->FindPin(UEdGraphSchema_K2::PN_Then),
	                                             BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventType)));

	// Get the beam flow (regular and event) for each flow pin that we dynamically created.
	const TArrayView<TArray<UEdGraphNode*>> PerFlowSlices = TArrayView<TArray<UEdGraphNode*>>{OutPerFlowNodes};
	const TArrayView<TArray<UEdGraphNode*>> PerFlowEventSlices = TArrayView<TArray<UEdGraphNode*>>{OutPerFlowEventNodes};
	const auto FlowIdxOffset = OthersFlowPin ? 2 : 1;
	const auto SuccessFlows = PerFlowSlices.Slice(FlowIdxOffset, SuccessSubEventsFlowPinNames.Num());
	const auto ErrorFlows = PerFlowSlices.Slice(FlowIdxOffset + SuccessSubEventsFlowPinNames.Num(), ErrorSubEventsFlowPinNames.Num());
	const auto CancelledFlows = PerFlowSlices.Slice(FlowIdxOffset + SuccessSubEventsFlowPinNames.Num() + ErrorSubEventsFlowPinNames.Num(), CancelledSubEventsFlowPinNames.Num());
	const auto SuccessEventFlows = PerFlowEventSlices.Slice(FlowIdxOffset, SuccessSubEventsFlowPinNames.Num());
	const auto ErrorEventFlows = PerFlowEventSlices.Slice(FlowIdxOffset + SuccessSubEventsFlowPinNames.Num(), ErrorSubEventsFlowPinNames.Num());
	const auto CancelledEventFlows = PerFlowEventSlices.Slice(FlowIdxOffset + SuccessSubEventsFlowPinNames.Num() + ErrorSubEventsFlowPinNames.Num(), CancelledSubEventsFlowPinNames.Num());

	// Expand the Success SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, SuccessFlows, SuccessEventFlows,
	                        OthersFlowPin, SuccessSubEventsFlowPinNames, SuccessSubEventsDataPinNames, RelevantSuccessSubEvents, SuccessSubEventsNotRelevantValues, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_SUCCESS))));

	// Expand the Error SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, ErrorFlows, ErrorEventFlows,
	                        OthersFlowPin, ErrorSubEventsFlowPinNames, ErrorSubEventsDataPinNames, RelevantErrorSubEvents, ErrorSubEventsNotRelevantValues, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_ERROR))));

	// Expand the Cancelled SubEvents
	ExpandBeamFlowSubEvents(CompilerContext, SourceGraph, K2Schema, CancelledFlows, CancelledEventFlows,
	                        OthersFlowPin, CancelledSubEventsFlowPinNames, CancelledSubEventsDataPinNames, RelevantCancelledSubEvents, CancelledSubEventsNotRelevantValues, BreakOperationResultNode,
	                        SwitchEnum->FindPin(StaticEnum<EBeamOperationEventType>()->GetNameByValue(static_cast<uint8>(EBeamOperationEventType::OET_CANCELLED))));

	for (int i = 0; i < OutPerFlowNodes.Num(); ++i)
	{
		// Get the data and request Id pins
		const auto IntermediateEventDataPin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventData));
		const auto IntermediateRequestIdPin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, RequestId));

		// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
		const TArray<UEdGraphPin*> NodePins{RequestIdPin, UserSlotsPin, OthersDataPin};
		const TArray<UEdGraphPin*> IntermediatePins{IntermediateRequestIdPin, IntermediateUserSlotPin, IntermediateEventDataPin};

		const auto Flow = OutPerFlowNodes[i];
		const auto EventFlow = OutPerFlowEventNodes[i];
		ReplaceConnectionsOnBeamFlow(Flow, NodePins, IntermediatePins);
		ReplaceConnectionsOnBeamFlow(EventFlow, NodePins, IntermediatePins);
	}

	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto IntermediateDelegatePin = IntermediateEventNode->FindPinChecked(IntermediateEventNode->DelegateOutputName);
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(IntermediateDelegatePin, OnCompleteDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_Operation::ExpandBeamFlowSubEvents(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
                                                    const TArrayView<TArray<UEdGraphNode*>> Flows, const TArrayView<TArray<UEdGraphNode*>> EventFlows,
                                                    UEdGraphPin* const OthersFlowPin, const TArray<FName> SubEventsFlowPins, const TArray<FName> SubEventsDataPins,
                                                    const TArray<uint8> SubEventsRelevantValues, const TArray<uint8> SubEventsSkippedValues,
                                                    UK2Node_BreakStruct* const BreakOperationResultNode, UEdGraphPin* const SubEventSwitchExecPin)
{
	const auto SubTypeCodePin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventSubTypeCode));
	const auto IntermediateEventDataPin = BreakOperationResultNode->FindPin(GET_MEMBER_NAME_CHECKED(FBeamOperationEvent, EventData));

	// Switch on it out of the success pin of the EventType switch
	const auto SubEventSwitch = CreateSwitchEnumNode(this, CompilerContext, SourceGraph, K2Schema, GetOperationSubTypeEnum(), SubEventSwitchExecPin, SubTypeCodePin);
	for (int i = 0; i < SubEventsFlowPins.Num(); ++i)
	{
		const auto FlowPin = FindPin(SubEventsFlowPins[i]);
		const auto DataPin = FindPin(SubEventsDataPins[i]);

		const auto SubEventValue = SubEventsRelevantValues[i];

		// Get the intermediate pins we'll need to connect to all the places our custom node's output pins are connected to.
		// If we expect a string, than we forward the raw event data string. Otherwise...
		auto IntermediateSubEventFlowPin = SubEventSwitch->FindPin(GetOperationSubTypeEnum()->GetNameByValue(SubEventValue));
		auto IntermediateSubEventDataPin = IntermediateEventDataPin;
		if (DataPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
		{
			// Based on the value, find the class and function we should call to convert from a string to an actual type.
			const auto ConvertClass = GetOperationSubTypeConversionFunctionClass().FindChecked(SubEventValue);
			const auto ConvertFunctionName = GetOperationSubTypeConversionFunctionName().FindChecked(SubEventValue);

			// We call a function to convert the String to the actual struct type and forward it along.
			// This conversion is defined by whatever function name we pass along.
			// It must be a BlueprintPure function that takes in a String and returns a struct of the type the OperationSubType expects 
			const auto CallConvertFunction = CreateCallFunctionNode(this, CompilerContext, SourceGraph, ConvertFunctionName, ConvertClass);

			const auto bConnectedConvertFlow = K2Schema->TryCreateConnection(IntermediateSubEventFlowPin, CallConvertFunction->GetExecPin());
			check(bConnectedConvertFlow)

			const auto bConnectedConvertData = K2Schema->TryCreateConnection(IntermediateEventDataPin, CallConvertFunction->GetPinWithDirectionAt(0, EGPD_Input));
			check(bConnectedConvertData)

			IntermediateSubEventFlowPin = CallConvertFunction->GetThenPin();
			IntermediateSubEventDataPin = CallConvertFunction->GetReturnValuePin();
		}

		// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
		const TArray<UEdGraphPin*> NodePins{DataPin};
		const TArray<UEdGraphPin*> IntermediatePins{IntermediateSubEventDataPin};

		const auto Flow = Flows[i];
		const auto EventFlow = EventFlows[i];
		ReplaceConnectionsOnBeamFlow(Flow, NodePins, IntermediatePins);
		ReplaceConnectionsOnBeamFlow(EventFlow, NodePins, IntermediatePins);

		// Get the flow pins
		const auto SuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*FlowPin, *IntermediateSubEventFlowPin);
		check(!SuccessFlowMoved.IsFatal());
	}

	// Move the execution flow of all non-captured cases to the others flow --- only if it exists.
	if (OthersFlowPin)
	{
		for (int i = 0; i < SubEventsSkippedValues.Num(); ++i)
		{
			const auto IntermediateNonRelevantFlowPin = SubEventSwitch->FindPin(GetOperationSubTypeEnum()->GetNameByValue(SubEventsSkippedValues[i]));
			const auto NonRelevantFlowMoved = CompilerContext.CopyPinLinksToIntermediate(*OthersFlowPin, *IntermediateNonRelevantFlowPin);
		}
	}
}

void UK2BeamNode_Operation::GatherSubEventsFromSubTypeEnum(const UEnum* Enum, TArray<FString>& SuccessTypeSubEvents, TArray<FString>& ErrorTypeSubEvents, TArray<FString>& CancelledTypeSubEvents)
{
	Enum->GetMetaData(TEXT("OperationSuccessSubEvents")).ParseIntoArray(SuccessTypeSubEvents, TEXT(","));
	Enum->GetMetaData(TEXT("OperationErrorSubEvents")).ParseIntoArray(ErrorTypeSubEvents, TEXT(","));
	Enum->GetMetaData(TEXT("OperationCancelledSubEvents")).ParseIntoArray(CancelledTypeSubEvents, TEXT(","));
}

#undef LOCTEXT_NAMESPACE
