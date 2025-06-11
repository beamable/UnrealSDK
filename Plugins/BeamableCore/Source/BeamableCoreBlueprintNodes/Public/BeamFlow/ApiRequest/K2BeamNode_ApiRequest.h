#pragma once

#include "BeamK2.h"
#include "K2Node_CallFunction.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"

#include "K2BeamNode_ApiRequest.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest"

/**
 * 
 */
UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_ApiRequest : public UK2BeamNode_BeamFlow
{
	GENERATED_BODY()

protected:
	const FName IP_ExecuteRequest_CallFunction_Request = FName("Request");

	const FName OP_ExecuteRequest_RequestContext = FName("Context");

	const FName OP_ExecuteRequest_OnSuccess = FName("OnSuccess");
	const FName OP_ExecuteRequest_Response = FName("Response");

	const FName OP_ExecuteRequest_OnError = FName("OnError");
	const FName OP_ExecuteRequest_Error = FName("Error");

	const FName OP_ExecuteRequest_OnComplete = FName("OnComplete");
	const FName OP_ExecuteRequest_Request = FName("Request");

	const FString OP_ExecuteRequest_RequestContext_Tooltip = FString("The context in which the request was made. This pin can be used on all 4 flows: Synchronous, Success, Error and Complete.");
	const FString OP_ExecuteRequest_Request_Tooltip = FString(
		"The request that was made. This pin can be used on all Success, Error and Complete execution flows, but not on the Synchronous Flow.");
	const FString OP_ExecuteRequest_OnSuccess_Tooltip = FString("This flow executes once if and when the request succeeds. Can only use the Context, Request and Response Pins.");
	const FString OP_ExecuteRequest_Response_Tooltip = FString("The response of the request in case successful. This pin can only be used on the Success Callback");
	const FString OP_ExecuteRequest_OnError_Tooltip = FString("This flow executes once for every failed request attempt. Can only use the Context, Request and Error Pins.");
	const FString OP_ExecuteRequest_Error_Tooltip = FString("The request that was made. This pin can be used on all Success, Error and Complete execution flows, but not on the Synchronous Flow.");
	const FString OP_ExecuteRequest_OnComplete_Tooltip = FString("This flow executes after OnSuccess/OnError. Can only use the Context and Request Pins.");


	const FString ExecuteRequest_ErrorPinInSuccessFlowMessage = LOCTEXT("InvalidPinInSuccessFlowOfBeamExecuteNode_Error",
	                                                                    "Node @@ in Success Flow is attempting to use the Error Pin! That is only available in the On Error Flow!")
		.
		ToString();

	const FString ExecuteRequest_ResponsePinInErrorFlowMessage = LOCTEXT("InvalidPinInErrorFlowOfBeamExecuteNode_Error",
	                                                                     "Node @@ in Error Flow is attempting to use the Response Pin! That is only available in the On Success Flow!")
		.
		ToString();

	const FString ExecuteRequest_ResponsePinInCompleteFlowMessage = LOCTEXT("InvalidErrorPinInCompleteFlowOfBeamExecuteNode_Error",
	                                                                        "Node @@ in Complete Flow is attempting to use the Response Pin! That is only available in the On Success Flow!")
		.ToString();

	const FString ExecuteRequest_ErrorPinInCompleteFlowMessage = LOCTEXT("InvalidErrorPinInCompleteFlowOfBeamExecuteNode_Error",
	                                                                     "Node @@ in Complete Flow is attempting to use the Error Pin! That is only available in the On Error Flow!")
		.ToString();

	const FString ExecuteRequest_ErrorPinInSynchronousFlowMessage = LOCTEXT("InvalidPinInSuccessFlowOfBeamExecuteNode_Error",
	                                                                        "Node @@ in Synchronous Flow is attempting to use the Error Pin! That is only available in the On Error Flow!")
		.
		ToString();

	const FString ExecuteRequest_ResponsePinInSynchronousFlowMessage = LOCTEXT("InvalidPinInSuccessFlowOfBeamExecuteNode_Error",
	                                                                           "Node @@ in Synchronous Flow is attempting to use the Response Pin! That is only available in the On Success Flow!")
		.
		ToString();


public:
	UPROPERTY()
	TArray<FString> WrappedRequestFunctionPinNames;

	UPROPERTY()
	TArray<FString> WrappedMakeFunctionPinNames;

	virtual FName GetSelfFunctionName() const;
	virtual FName GetRequestFunctionName() const;
	virtual FName GetMakeFunctionName() const;

	virtual FString GetServiceName() const override;
	virtual FString GetEndpointName() const;
	virtual UClass* GetApiClass() const;
	virtual UClass* GetRequestClass() const;
	virtual UClass* GetResponseClass() const;
	virtual FString GetRequestSuccessDelegateName() const;
	virtual FString GetRequestErrorDelegateName() const;
	virtual FString GetRequestCompleteDelegateName() const;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetMenuCategory() const override;

	virtual void AllocateDefaultPins() override;
	static bool IsIgnoredInputPinForExecuteRequestNode(const UEdGraphNode* CustomNode, const FProperty* Param);

	void CreateExecuteRequestPins(UClass* RequestTypeClass);
	void CreateBeamFlowModePins(UClass* ResponseTypeClass);

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	
	void SetUpInputPinsForMakeAndRequestNodes(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
	                                          const UK2Node_CallFunction* CallMakeFunction, UEdGraphPin* ExecutionPin);

	static void SetUpPinsForSynchronousBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
	                                            const UK2Node_CallFunction* CallMakeFunction, const TArray<UEdGraphNode*>& OutPerFlowNodes,
	                                            const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                            UEdGraphPin* ThenPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin);

	static void SetUpPinsForSynchronousFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
	                                        const UK2Node_CallFunction* CallMakeFunction, const TArray<UEdGraphNode*>& OutPerFlowNodes,
	                                        const TArray<UEdGraphNode*>& OutPerFlowEventNodes, UEdGraphPin* ThenPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin);

	void SetUpPinsForOnSuccessBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* SuccessEventNode,
	                                   const TArray<UEdGraphNode*>& SuccessFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                   UEdGraphPin* SuccessPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const;

	void SetUpPinsForOnErrorBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* ErrorEventNode,
	                                 const TArray<UEdGraphNode*>& ErrorFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                 UEdGraphPin* ErrorPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const;

	void SetUpPinsForOnCompleteBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* CompleteEventNode,
	                                    const TArray<UEdGraphNode*>& CompleteFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
	                                    UEdGraphPin* CompletePin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const;


	virtual void EnterBeamFlowModeImpl() override;
	virtual void ExitBeamFlowModeImpl() override;
};

#undef LOCTEXT_NAMESPACE
