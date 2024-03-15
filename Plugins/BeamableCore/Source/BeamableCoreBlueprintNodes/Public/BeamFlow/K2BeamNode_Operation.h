// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2BeamNode_BeamFlow.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_CallFunction.h"
#include "RequestTracker/BeamOperation.h"
#include "K2BeamNode_Operation.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation"

class UK2Node_Event;

UENUM(BlueprintType)
enum EOperationNodeModes
{
	OnCompleted,
	Success_NonSuccess,
	Success_Error_Cancelled,
	OnSubEvents
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation : public UK2BeamNode_BeamFlow
{
	GENERATED_BODY()

	const FName OP_Operation_Handle = FName("Operation Handle");

	const FName OP_Operation_OnOperationEvent = FName("OnOperationEvent");
	const FName OP_Operation_UserSlots = FName("UserSlots");
	const FName OP_Operation_Event = FName("OperationEvent");

	const FName OP_Operation_Expanded_ErrorData = FName(TEXT("ErrorData"));
	const FName OP_Operation_Expanded_SuccessData = FName(TEXT("SuccessData"));
	const FName OP_Operation_Expanded_CancelledData = FName(TEXT("CancelledData"));
	const FName OP_Operation_Expanded_EventData = FName(TEXT("EventData"));

	const FName OP_Operation_Expanded_OnSuccess = FName(TEXT("OnSuccess"));
	const FName OP_Operation_Expanded_OnError = FName(TEXT("OnError"));
	const FName OP_Operation_Expanded_OnCancelled = FName(TEXT("OnCancelled"));
	const FName OP_Operation_Expanded_OnOthers = FName(TEXT("OnOthers"));

	const FString Operation_InvalidPinInFlowMessage = LOCTEXT("InvalidPinInFlowOfBeamOperationNode_Error",
	                                                          "Node @@ in {0} Flow is attempting to use the {1} Pin! That is only available on {2} Flow(s)!")
		.
		ToString();

	const FString Operation_UserSlotsPinInSynchronousFlowMessage = FString::Format(*Operation_InvalidPinInFlowMessage,
	                                                                               {TEXT("Synchronous"), *OP_Operation_UserSlots.ToString(), TEXT("Non-Synchronous")});
	const FString Operation_ResultPinInSynchronousFlowMessage = FString::Format(*Operation_InvalidPinInFlowMessage,
	                                                                            {TEXT("Synchronous"), *OP_Operation_Event.ToString(), TEXT("the OnComplete")});	
	const FString Operation_ErrorPinInSynchronousFlowMessage = FString::Format(*Operation_InvalidPinInFlowMessage,
	                                                                           {TEXT("Synchronous"), *OP_Operation_Expanded_ErrorData.ToString(), TEXT("any Error")});

	const FString Operation_DataPinInSynchronousFlowMessage = FString::Format(*Operation_InvalidPinInFlowMessage,
	                                                                          {TEXT("Synchronous"), *OP_Operation_Expanded_EventData.ToString(), TEXT("any Non-Synchronous")});

	

	/**
	 * @brief Just a display on whether or not this is a Multi User Operation. This changes the semantics of the node a bit.
	 */
	UPROPERTY(VisibleAnywhere, Category="Beam|Operations")
	bool bIsMultiUser;


	UPROPERTY(EditAnywhere, Category="Beam Flow|Operations")
	TEnumAsByte<EOperationNodeModes> CurrentExpandedMode{OnCompleted};

	/**
	 * @brief We keep track of the sub events we care about. By default, we care about the final success/error/cancel event that the operation emits.
	 * All cases that you don't explicitly care about when you declare your own operation-specific enum are handled by a catch-all "others" flow.	 
	 */
	UPROPERTY(EditAnywhere, Category="Beam Flow|Operations")
	TArray<FName> RelevantSuccessEventCodes{NAME_None};
	UPROPERTY(EditAnywhere, Category="Beam Flow|Operations")
	TArray<FName> RelevantErrorEventCodes{NAME_None};
	UPROPERTY(EditAnywhere, Category="Beam Flow|Operations")
	TArray<FName> RelevantCancelledEventCodes{NAME_None};
	UPROPERTY()
	TArray<FName> IrrelevantSuccessEventCodes;
	UPROPERTY()
	TArray<FName> IrrelevantErrorEventCodes;
	UPROPERTY()
	TArray<FName> IrrelevantCancelledEventCodes;

	UPROPERTY()
	TArray<FName> SuccessEventFlowPinNames;
	UPROPERTY()
	TArray<FName> ErrorEventFlowPinNames;
	UPROPERTY()
	TArray<FName> CancelledEventFlowPinNames;
	UPROPERTY()
	TArray<FName> SuccessEventDataPinNames;
	UPROPERTY()
	TArray<FName> ErrorEventDataPinNames;
	UPROPERTY()
	TArray<FName> CancelledEventDataPinNames;

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionInputPinNames;


	//UK2Node impl
	virtual void AllocateDefaultPins() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	//BeamFlowNode impl


protected:
	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;

	/**
	 * @brief The subsystem's Operation function. This is any function that returns a FBeamOperationHandle and has a 'FBeamOperationEventHandler OnOperationEvent' parameter.
	 */
	virtual FName GetOperationFunctionName() const;

	/**
	 * @brief Override this to modify and override the tooltips for pin names. Gets recreated every time EnforceBeamFlowModePins gets called.  
	 * @param OutTooltipMap The map to fill with all the tooltips.
	 */
	virtual void BuildPinToolTipMap(TMap<FName, FString>& OutTooltipMap);

	/**
	 * @brief The UClass for a subsystem (GameInstanceSubsystem or BeamRuntimeSubsystem) that this operation resides in. 
	 */
	virtual UClass* GetRuntimeSubsystemClass() const;

	/**
	 * Returns the list of possible values for FBeamOperationEvent.EventCode given the type of the event (success/error/etc).
	 * Must always include NAME_None as its first value (the base implementation guarantees this) so call it if you override this to expose other events. 
	 */
	virtual TArray<FName>   GetOperationEventCodes(EBeamOperationEventType Type) const;

	/**
	 * Array parallel to the ones returned by GetOperationEventCodes that describes the tooltips for the pins of each individual sub events when in EOperationNodeModes::OnSubEvents mode. 
	 */
	virtual TArray<FString> GetOperationEventCodeTooltips(EBeamOperationEventType Type) const;	

	/**
	 * @brief Map of pin names to tooltip.
	 */
	TMap<FName, FString> PinTooltipMap;
	
	//BeamFlowNode impl
	virtual void EnterBeamFlowModeImpl() override;
	virtual void ExitBeamFlowModeImpl() override;
	//End BeamFlowNode impl

	static bool IsIgnoredInputPinForExecuteRequestNode(const UEdGraphNode* CustomNode, const FProperty* Param);
	void EnforceOperationPins();
	void EnforceBeamFlowModePins();

	void ExpandNonBeamFlowMode(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallOperationFunction,
	                           UEdGraphPin* const ThenPin, UEdGraphPin* const HandlePin);
	void ExpandBeamFlowMode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
	                        UEdGraphPin* const ThenPin);


	void SetUpInputPinsForOperationNode(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin* ExecutionPin);
	void SetUpPinsForSynchronousFlow(FKismetCompilerContext& CompilerContext, const TArray<UEdGraphNode*>& SyncFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                 const UK2Node_CallFunction* CallOperationFunction, UEdGraphPin*
	                                 ThenPin, UEdGraphPin* HandlePin);
	void SetUpPinsForOnCompleteBeamFlow(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
	                                    const TArray<UEdGraphNode*>& CompleteFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                    UEdGraphPin* CompletePin, UEdGraphPin* ResultPin, UEdGraphPin* UserSlotsPin);

	void SetUpPinsForSuccessNotSuccessBeamFlow(FKismetCompilerContext&       CompilerContext, UEdGraph*       SourceGraph, const UK2Node_CallFunction*     CallOperationFunction, UEdGraphPin* const SuccessFlowPin,
	                                           UEdGraphPin* const            UserSlotsPin, UEdGraphPin* const OthersFlowPin, TArray<TArray<UEdGraphNode*>> OutPerFlowNodes,
	                                           TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes);

	void SetUpPinsForSuccessErrorCancelledBeamFlow(FKismetCompilerContext&       CompilerContext, UEdGraph*                     SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
	                                               UEdGraphPin* const            SuccessFlowPin, UEdGraphPin* const             UserSlotsPin,
	                                               UEdGraphPin* const            ErrorFlowPin, UEdGraphPin* const               EventDataPin, UEdGraphPin* const CancelledFlowPin,
	                                               TArray<TArray<UEdGraphNode*>> OutPerFlowNodes, TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes);

	void SetUpPinsForSubEventsBeamFlow(FKismetCompilerContext&       CompilerContext, UEdGraph*       SourceGraph, const UK2Node_CallFunction* CallOperationFunction,
	                                   UEdGraphPin* const            UserSlotsPin, UEdGraphPin* const OthersFlowPin, UEdGraphPin* const        OthersDataPin, TArray<TArray<UEdGraphNode*>> OutPerFlowNodes,
	                                   TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes);

	void ExpandBeamFlowSubEvents(FKismetCompilerContext&                 CompilerContext, UEdGraph*                     SourceGraph, const UEdGraphSchema_K2* K2Schema,
	                             const TArrayView<TArray<UEdGraphNode*>> Flows, const TArrayView<TArray<UEdGraphNode*>> EventFlows,
	                             UEdGraphPin* const                      OthersFlowPin,
	                             const TArray<FName>&                    EventsFlowPinNames,
	                             const TArray<FName>&                    EventsDataPinNames, const TArray<FName>&         RelevantEventCodes,
	                             const TArray<FName>&                    IrrelevantEventCodes, UK2Node_BreakStruct* const BreakOperationResultNode, UEdGraphPin* const SubEventSwitchExecPin);
	
};

#undef LOCTEXT_NAMESPACE
