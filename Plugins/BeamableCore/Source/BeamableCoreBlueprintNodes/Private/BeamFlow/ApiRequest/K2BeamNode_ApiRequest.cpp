#include "BeamFlow/ApiRequest/K2BeamNode_ApiRequest.h"

#include "KismetCompiler.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamRequestContext.h"
#include "RequestTracker/BeamRequestTracker.h"


using namespace BeamK2;

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest"


FName UK2BeamNode_ApiRequest::GetSelfFunctionName() const
{
	return FName("Should be code-gen'ed to return what is commented for each request"); // GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);	
}

FName UK2BeamNode_ApiRequest::GetRequestFunctionName() const
{
	return FName("Should be code-gen'ed to return what is commented for each request"); // GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetMe);
}

FName UK2BeamNode_ApiRequest::GetMakeFunctionName() const
{
	return FName("Should be code-gen'ed to return what is commented for each request"); // GET_FUNCTION_NAME_CHECKED(UBasicAccountsGetMeRequest, MakeBasicAccountsGetMeRequest);
}

FString UK2BeamNode_ApiRequest::GetServiceName() const
{
	return FString("NullService");
}

FString UK2BeamNode_ApiRequest::GetEndpointName() const
{
	return FString("NullEndpoint");
}

UClass* UK2BeamNode_ApiRequest::GetApiClass() const
{
	return UClass::StaticClass();
}

UClass* UK2BeamNode_ApiRequest::GetRequestClass() const
{
	return UClass::StaticClass();
}

UClass* UK2BeamNode_ApiRequest::GetResponseClass() const
{
	return UClass::StaticClass();
}

FString UK2BeamNode_ApiRequest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnNullSuccess");
}

FString UK2BeamNode_ApiRequest::GetRequestErrorDelegateName() const
{
	return TEXT("OnNullError");
}

FString UK2BeamNode_ApiRequest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnNullComplete");
}

FText UK2BeamNode_ApiRequest::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(FString::Printf(TEXT("LowLevel - %s - %s"), *GetServiceName(), *GetEndpointName()));
}

FText UK2BeamNode_ApiRequest::GetMenuCategory() const
{
	return FText::FromString(FString::Printf(TEXT("Beam|%s|LowLevel"), *GetServiceName()));
}

void UK2BeamNode_ApiRequest::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto _ = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	const auto RequestFunction = GetApiClass()->FindFunctionByName(GetRequestFunctionName());

	// Create the input pins for this ExecuteRequest node
	// Start by grabbing the request function, which give us the output pins of the graph this node hides as well as a couple of the input ones.	
	ParseFunctionForNodeInputPins(this, RequestFunction, WrappedRequestFunctionPinNames, IsIgnoredInputPinForExecuteRequestNode);
	// Then, grab the Make___Request function. This give us the the data input pins of the graph this node hides.
	ParseFunctionForNodeInputPins(this, GetRequestClass()->FindFunctionByName(GetMakeFunctionName()), WrappedMakeFunctionPinNames, IsIgnoredInputPinForExecuteRequestNode);

	// Create the output pins in an order that improves usability.
	CreateExecuteRequestPins(GetRequestClass());
	if (bIsInBeamFlowMode)
		CreateBeamFlowModePins(GetResponseClass());
	else
		ParseFunctionForNodeInputPins(this, RequestFunction, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete}, true);
}


bool UK2BeamNode_ApiRequest::IsIgnoredInputPinForExecuteRequestNode(const UEdGraphNode* CustomNode, const FProperty* Param)
{
	// We ignore all delegate types that start with On (OnSuccess, OnError, OnComplete)
	const bool bIsResponseDelegate = Param->GetFName().ToString().StartsWith(TEXT("On"));

	// We ignore all "Request" named parameters of any UBeamBaseRequestInterface implementations because we'll use the Make____Request functions to create these under the hood.
	const bool bIsRequestParam = Param->GetOwnerClass()->GetName().StartsWith(TEXT("Beam")) &&
		Param->GetOwnerClass()->GetName().EndsWith(TEXT("Api")) &&
		Param->GetFName().ToString() == TEXT("Request");

	// We ignore all Output parameters because we create these by hand.
	const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

	// We also ignore duplicated pin names. This is by design for now --- TODO: We need to resolve name collisions differently as this can easily hide bugs.
	const UEdGraphPin* EdGraphPin = CustomNode->FindPin(Param->GetFName());

	// Any of these are true, and the param doesn't become an input pin.
	return bIsRequestParam || bIsResponseDelegate || bIsOutputParam || EdGraphPin;
}

void UK2BeamNode_ApiRequest::CreateExecuteRequestPins(UClass* RequestTypeClass)
{
	const auto SynchronousFlowPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	const auto ContextPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamRequestContext::StaticStruct(), OP_ExecuteRequest_RequestContext);
	const auto RequestPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, RequestTypeClass, OP_ExecuteRequest_Request);
	SynchronousFlowPin->PinFriendlyName = LOCTEXT("BeamNode", "Synchronous Flow");
	ContextPin->PinToolTip = OP_ExecuteRequest_RequestContext_Tooltip;
	RequestPin->PinToolTip = OP_ExecuteRequest_Error_Tooltip;
}

void UK2BeamNode_ApiRequest::CreateBeamFlowModePins(UClass* ResponseTypeClass)
{
	const auto OnCompletePin = this->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_ExecuteRequest_OnComplete);
	const auto OnSuccessFlowPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_ExecuteRequest_OnSuccess);
	const auto ResponsePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, ResponseTypeClass, OP_ExecuteRequest_Response);
	const auto OnErrorPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, OP_ExecuteRequest_OnError);
	const auto ErrorPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamErrorResponse::StaticStruct(), OP_ExecuteRequest_Error);
	OnSuccessFlowPin->PinToolTip = OP_ExecuteRequest_OnSuccess_Tooltip;
	OnErrorPin->PinToolTip = OP_ExecuteRequest_OnError_Tooltip;
	OnCompletePin->PinToolTip = OP_ExecuteRequest_OnComplete_Tooltip;
	ResponsePin->PinToolTip = OP_ExecuteRequest_Response_Tooltip;
	ErrorPin->PinToolTip = OP_ExecuteRequest_Request_Tooltip;
}

void UK2BeamNode_ApiRequest::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const UK2Node_CallFunction* CallGetSubsystem = CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSelfFunctionName(), GetApiClass());
	const UK2Node_CallFunction* CallRequestFunction = CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetRequestFunctionName(), GetApiClass());
	const UK2Node_CallFunction* CallMakeFunction = CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetMakeFunctionName(), GetRequestClass());

	const UK2Node_Event* SuccessEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, GetRequestSuccessDelegateName());
	const UK2Node_Event* ErrorEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, GetRequestErrorDelegateName());
	const UK2Node_Event* CompleteEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, GetRequestCompleteDelegateName());

	// Gets all relevant pins
	const auto ExecutionPin = K2Schema->FindExecutionPin(*this, EGPD_Input);
	if (ExecutionPin->LinkedTo.Num() > 1)
		CompilerContext.MessageLog.Error(TEXT("@@ has more than one input! Beam Flow nodes do not allow that!"), this);

	const auto ThenPin = K2Schema->FindExecutionPin(*this, EGPD_Output);
	const auto SuccessFlowPin = FindPin(OP_ExecuteRequest_OnSuccess);
	const auto ErrorFlowPin = FindPin(OP_ExecuteRequest_OnError);
	const auto CompleteFlowPin = FindPin(OP_ExecuteRequest_OnComplete);
	const auto ContextPin = FindPin(OP_ExecuteRequest_RequestContext);
	const auto RequestPin = FindPin(OP_ExecuteRequest_Request);
	const auto ErrorPin = FindPin(OP_ExecuteRequest_Error);
	const auto ResponsePin = FindPin(OP_ExecuteRequest_Response);

	// Split out all the nodes for each "sub-graph": OnSuccess Sub-Graph, OnError Sub-Graph and OnComplete Sub-Graph. 
	if (bIsInBeamFlowMode)
	{
		const TArray<UEdGraphPin*> StartingGraphs{SuccessFlowPin, ErrorFlowPin, CompleteFlowPin, ThenPin,};
		const TArray<FName> RelevantFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
		TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
		TArray<TArray<UEdGraphNode*>> OutPerFlowEventNodes;
		GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantFunctionNames, OutPerFlowNodes, OutPerFlowEventNodes);

		// Validate that the Success Flow does not use the Error Pin
		ValidateOutputPinUsage(CompilerContext, {ErrorPin}, {ExecuteRequest_ErrorPinInSuccessFlowMessage}, OutPerFlowNodes[0]);

		// Validate that the Error Flow does not use the Response Pin
		ValidateOutputPinUsage(CompilerContext, {ResponsePin}, {ExecuteRequest_ResponsePinInErrorFlowMessage}, OutPerFlowNodes[1]);

		// Validate that the Complete Flow does not use the Error OR the Response Pin
		ValidateOutputPinUsage(CompilerContext, {ResponsePin, ErrorPin}, {ExecuteRequest_ResponsePinInCompleteFlowMessage, ExecuteRequest_ErrorPinInCompleteFlowMessage},
		                       OutPerFlowNodes[2]);

		// Validate that the Synchronous Flow does not use the Request, Error OR the Response Pin
		// If there Wait Events complete events being declared in the Synchronous Flow, we can't know at compile time which pins are valid.
		// It becomes the responsibility of the user if they desire to do respond to events using pins from these nodes.
		// They can always get at the data by accessing and casting the correct response based on the status stored in the RequestContext when they WaitAll/Any.
		// They just have to cast the IBeamBaseRequestInterface and UObjects to the expected types manually. We provide auto-cast functions to make Node less annoying when it happens.
		ValidateOutputPinUsage(CompilerContext, {ResponsePin, ErrorPin}, {ExecuteRequest_ResponsePinInSynchronousFlowMessage, ExecuteRequest_ErrorPinInSynchronousFlowMessage},
		                       OutPerFlowNodes[3]);

		// Connects the result of the "static BeamApi::GetSelf" call to the "non-static BeamApi::Verb____" Call Function node.
		SetUpPinsFunctionToOwnerSubsystem(CallGetSubsystem, CallRequestFunction);

		// Set up Input pins for both expanded nodes: "Make" and "CallRequest"
		SetUpInputPinsForMakeAndRequestNodes(CompilerContext, CallRequestFunction, CallMakeFunction, ExecutionPin);


		// Make sure all output pins in Node node relevant to the success callback that are connected to nodes in the success flow are correctly configured.
		SetUpPinsForOnSuccessBeamFlow(CompilerContext, CallRequestFunction, SuccessEventNode, OutPerFlowNodes[0], OutPerFlowEventNodes[0],
		                              SuccessFlowPin, ContextPin, RequestPin);

		// Make sure all output pins in Node node relevant to the error callback that are connected to nodes in the error flow are correctly configured.	
		SetUpPinsForOnErrorBeamFlow(CompilerContext, CallRequestFunction, ErrorEventNode, OutPerFlowNodes[1], OutPerFlowEventNodes[1],
		                            ErrorFlowPin, ContextPin, RequestPin);

		// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the complete flow are correctly configured.
		SetUpPinsForOnCompleteBeamFlow(CompilerContext, CallRequestFunction, CompleteEventNode, OutPerFlowNodes[2], OutPerFlowEventNodes[2],
		                               CompleteFlowPin, ContextPin, RequestPin);

		// Make sure all output pins in Node node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
		SetUpPinsForSynchronousBeamFlow(CompilerContext, CallRequestFunction, CallMakeFunction, OutPerFlowNodes[3], OutPerFlowEventNodes[3],
		                                ThenPin, ContextPin, RequestPin);
	}
	else
	{
		const TArray<UEdGraphPin*> StartingGraphs{ThenPin,};
		TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
		TArray<TArray<UEdGraphNode*>> OutPerEventFlowNodes;
		GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, {}, OutPerFlowNodes, OutPerEventFlowNodes);

		// Connects the result of the "static BeamApi::GetSelf" call to the "non-static BeamApi::Verb____" Call Function node.
		SetUpPinsFunctionToOwnerSubsystem(CallGetSubsystem, CallRequestFunction);

		// Set up Input pins for both expanded nodes: "Make" and "CallRequest"
		SetUpInputPinsForMakeAndRequestNodes(CompilerContext, CallRequestFunction, CallMakeFunction, ExecutionPin);

		// Move the connected delegate pins over to the Call Request Function
		MoveWrappedPin(this, CompilerContext, CallRequestFunction, OP_ExecuteRequest_OnSuccess);
		MoveWrappedPin(this, CompilerContext, CallRequestFunction, OP_ExecuteRequest_OnError);
		MoveWrappedPin(this, CompilerContext, CallRequestFunction, OP_ExecuteRequest_OnComplete);

		// Make sure all output pins in this node relevant to the complete callback that are connected to nodes in the synchronous flow are correctly configured.
		SetUpPinsForSynchronousFlow(CompilerContext, CallRequestFunction, CallMakeFunction, OutPerFlowNodes[0], OutPerEventFlowNodes[0],
		                            ThenPin, ContextPin, RequestPin);
	}


	// This needs to exist so that the custom node is no longer in the graph and gets killed off when we cook the Blueprint.
	// This works because we fully replace and guarantee the execution flow is correctly set up.
	BreakAllNodeLinks();
}

void UK2BeamNode_ApiRequest::SetUpInputPinsForMakeAndRequestNodes(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
                                                                  const UK2Node_CallFunction* CallMakeFunction, UEdGraphPin* ExecutionPin)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the execution pin from the CallRequest node
	const auto CallRequestFunctionExecPin = CallRequestFunction->FindPinChecked(UEdGraphSchema_K2::PN_Execute);

	// Moves the execution flow from the default "Then" execution pin of this custom node to the "Then" Exec pin of the "____ Request" CallFunction node.	
	const auto MovedRegularExecutionFlow = CompilerContext.MovePinLinksToIntermediate(*ExecutionPin, *CallRequestFunctionExecPin);
	check(!MovedRegularExecutionFlow.IsFatal())


	// We start by moving all the input pins that this custom node takes in into the "Make ____ Request" node's ones.		
	for (const auto& WrappedFunctionPin : WrappedMakeFunctionPinNames)
	{
		if (const auto FunctionPin = CallMakeFunction->FindPin(WrappedFunctionPin))
		{
			const auto Pin = this->FindPin(WrappedFunctionPin);
			UE_LOG(LogTemp, Verbose, TEXT("Looking at Make Function Pin %s, %d"), *FunctionPin->PinName.ToString(), WrappedMakeFunctionPinNames.Num())

			// We should not be doing this more than once for each input pin --- if we do that's a critical BUG: and we need to sort out why and fix it.
			// The BUG is that the latter connection would override the first one. 
			checkf(!FunctionPin->HasAnyConnections(), TEXT("PinName=%s"), *FunctionPin->PinName.ToString())
			CompilerContext.MovePinLinksToIntermediate(*Pin, *FunctionPin);
		}
	}

	// The we get the output pin of the Call Make node and connect it to the Call Request Node
	const auto CallMakeFunctionReturnValuePin = CallMakeFunction->GetReturnValuePin();
	const auto CallRequestFunctionRequestPin = CallRequestFunction->FindPinChecked(IP_ExecuteRequest_CallFunction_Request);
	const auto bConnectedMakeReturnToRequestInput = K2Schema->TryCreateConnection(CallMakeFunctionReturnValuePin, CallRequestFunctionRequestPin);
	check(bConnectedMakeReturnToRequestInput)

	// Finally, we move all the rest of the parameters into 
	for (const auto& WrappedFunctionPin : WrappedRequestFunctionPinNames)
	{
		if (const auto FunctionPin = CallRequestFunction->FindPin(WrappedFunctionPin))
		{
			const auto Pin = this->FindPin(WrappedFunctionPin);
			UE_LOG(LogTemp, Verbose, TEXT("Looking at Request Function Pin %s, %d"), *FunctionPin->PinName.ToString(), WrappedMakeFunctionPinNames.Num())

			// We should not be doing this more than once for each input pin --- if we do that's a critical BUG: and we need to sort out why and fix it.
			// The BUG is that the latter connection would override the first one. 
			checkf(!FunctionPin->HasAnyConnections(), TEXT("PinName=%s"), *FunctionPin->PinName.ToString())
			CompilerContext.MovePinLinksToIntermediate(*Pin, *FunctionPin);
		}
	}
}

void UK2BeamNode_ApiRequest::SetUpPinsForSynchronousBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
                                                             const UK2Node_CallFunction* CallMakeFunction, const TArray<UEdGraphNode*>& OutPerFlowNodes,
                                                             const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
                                                             UEdGraphPin* ThenPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin)
{
	const auto CallRequestThenPin = CallRequestFunction->GetThenPin();
	const auto CallRequestContextPin = CallRequestFunction->FindPin(FName(TEXT("OutRequestContext")));
	const auto MakeReturnValuePin = CallMakeFunction->GetReturnValuePin();

	const TArray<UEdGraphPin*> SyncFlowAllowedPins{ContextPin, RequestPin};
	const TArray<UEdGraphPin*> SyncFlowTargetPins{CallRequestContextPin, MakeReturnValuePin};
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes, SyncFlowAllowedPins, SyncFlowTargetPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, SyncFlowAllowedPins, SyncFlowTargetPins);

	// -- Tie the flow of the CallFunction Then pin (Output Execution pin) to the node which the Synchronous Flow pin is connected.
	const auto MovedRegularThenFlow = CompilerContext.MovePinLinksToIntermediate(*ThenPin, *CallRequestThenPin);
	check(!MovedRegularThenFlow.IsFatal())
}

void UK2BeamNode_ApiRequest::SetUpPinsForSynchronousFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction,
                                                         const UK2Node_CallFunction* CallMakeFunction, const TArray<UEdGraphNode*>& OutPerFlowNodes,
                                                         const TArray<UEdGraphNode*>& OutPerFlowEventNodes, UEdGraphPin* ThenPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin)
{
	const auto CallRequestThenPin = CallRequestFunction->GetThenPin();
	const auto CallRequestContextPin = CallRequestFunction->FindPin(FName(TEXT("OutRequestContext")));
	const auto MakeReturnValuePin = CallMakeFunction->GetReturnValuePin();

	const TArray<UEdGraphPin*> SyncFlowAllowedPins{ContextPin, RequestPin};
	const TArray<UEdGraphPin*> SyncFlowTargetPins{CallRequestContextPin, MakeReturnValuePin};
	ReplaceConnectionsOnBeamFlow(OutPerFlowNodes, SyncFlowAllowedPins, SyncFlowTargetPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, SyncFlowAllowedPins, SyncFlowTargetPins);

	// -- Tie the flow of the CallFunction Then pin (Output Execution pin) to the node which the Synchronous Flow pin is connected.
	const auto MovedRegularThenFlow = CompilerContext.MovePinLinksToIntermediate(*ThenPin, *CallRequestThenPin);
	check(!MovedRegularThenFlow.IsFatal())
}


void UK2BeamNode_ApiRequest::SetUpPinsForOnSuccessBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* SuccessEventNode,
                                                           const TArray<UEdGraphNode*>& SuccessFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
                                                           UEdGraphPin* SuccessPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const auto SuccessResponsePin = this->FindPinChecked(OP_ExecuteRequest_Response);
	const auto CallRequestFunctionDelegatePin = CallRequestFunction->FindPinChecked(OP_ExecuteRequest_OnSuccess, EGPD_Input);

	const auto SuccessEventNodeExecPin = SuccessEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
	const auto SuccessEventDelegatePin = SuccessEventNode->FindPinChecked(SuccessEventNode->DelegateOutputName);
	const auto SuccessEventNodeContextPin = SuccessEventNode->FindPinChecked(OP_ExecuteRequest_RequestContext);
	const auto SuccessEventNodeRequestPin = SuccessEventNode->FindPinChecked(OP_ExecuteRequest_Request);
	const auto SuccessEventNodeResponsePin = SuccessEventNode->FindPinChecked(OP_ExecuteRequest_Response);


	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> SuccessPins{ContextPin, RequestPin, SuccessResponsePin};
	const TArray<UEdGraphPin*> SuccessEventPins{SuccessEventNodeContextPin, SuccessEventNodeRequestPin, SuccessEventNodeResponsePin};
	ReplaceConnectionsOnBeamFlow(SuccessFlowNodes, SuccessPins, SuccessEventPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, SuccessPins, SuccessEventPins);

	// Move the execution flow from the "On Success" pin to the "Then" execution pin of the SuccessEvent node.  
	const auto ExecFlowMoved = CompilerContext.MovePinLinksToIntermediate(*SuccessPin, *SuccessEventNodeExecPin);
	check(!ExecFlowMoved.IsFatal());
	// Connect the SuccessEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnSuccess" delegate pin.
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(SuccessEventDelegatePin, CallRequestFunctionDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_ApiRequest::SetUpPinsForOnErrorBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* ErrorEventNode,
                                                         const TArray<UEdGraphNode*>& ErrorFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes,
                                                         UEdGraphPin* ErrorPin, UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const auto ErrorResponsePin = this->FindPinChecked(OP_ExecuteRequest_Error);
	const auto CallRequestFunctionDelegatePin = CallRequestFunction->FindPinChecked(OP_ExecuteRequest_OnError, EGPD_Input);
	const auto ErrorEventNodeExecPin = ErrorEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
	const auto ErrorEventDelegatePin = ErrorEventNode->FindPinChecked(ErrorEventNode->DelegateOutputName);
	const auto ErrorEventNodeRequestIdPin = ErrorEventNode->FindPinChecked(OP_ExecuteRequest_RequestContext);
	const auto ErrorEventNodeRequestPin = ErrorEventNode->FindPinChecked(OP_ExecuteRequest_Request);
	const auto ErrorEventNodeResponsePin = ErrorEventNode->FindPinChecked(OP_ExecuteRequest_Error);


	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> ErrorPins{ContextPin, RequestPin, ErrorResponsePin};
	const TArray<UEdGraphPin*> ErrorEventPins{ErrorEventNodeRequestIdPin, ErrorEventNodeRequestPin, ErrorEventNodeResponsePin};
	ReplaceConnectionsOnBeamFlow(ErrorFlowNodes, ErrorPins, ErrorEventPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, ErrorPins, ErrorEventPins);

	// Move the execution flow from the "On Error" pin to the "Then" execution pin of the ErrorEvent node.  
	const auto ExecFlowMoved = CompilerContext.MovePinLinksToIntermediate(*ErrorPin, *ErrorEventNodeExecPin);
	check(!ExecFlowMoved.IsFatal());
	// Connect the ErrorEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnError" delegate pin.
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(ErrorEventDelegatePin, CallRequestFunctionDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_ApiRequest::SetUpPinsForOnCompleteBeamFlow(FKismetCompilerContext& CompilerContext, const UK2Node_CallFunction* CallRequestFunction, const UK2Node_Event* CompleteEventNode,
                                                            const TArray<UEdGraphNode*>& CompleteFlowNodes, const TArray<UEdGraphNode*>& OutPerFlowEventNodes, UEdGraphPin* CompletePin,
                                                            UEdGraphPin* ContextPin, UEdGraphPin* RequestPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const auto CallRequestFunctionDelegatePin = CallRequestFunction->FindPinChecked(OP_ExecuteRequest_OnComplete, EGPD_Input);
	const auto CompleteEventNodeExecPin = CompleteEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
	const auto CompleteEventDelegatePin = CompleteEventNode->FindPinChecked(CompleteEventNode->DelegateOutputName);
	const auto CompleteEventNodeRequestIdPin = CompleteEventNode->FindPinChecked(OP_ExecuteRequest_RequestContext);
	const auto CompleteEventNodeRequestPin = CompleteEventNode->FindPinChecked(OP_ExecuteRequest_Request);


	// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
	const TArray<UEdGraphPin*> CompletePins{ContextPin, RequestPin};
	const TArray<UEdGraphPin*> CompleteEventPins{CompleteEventNodeRequestIdPin, CompleteEventNodeRequestPin};
	ReplaceConnectionsOnBeamFlow(CompleteFlowNodes, CompletePins, CompleteEventPins);
	ReplaceConnectionsOnBeamFlow(OutPerFlowEventNodes, CompletePins, CompleteEventPins);

	// Move the execution flow from the "On Complete" pin to the "Then" execution pin of the CompleteEvent node.  
	const auto ExecFlowMoved = CompilerContext.MovePinLinksToIntermediate(*CompletePin, *CompleteEventNodeExecPin);
	check(!ExecFlowMoved.IsFatal());
	// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Call Function node "OnComplete" delegate pin.
	const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(CompleteEventDelegatePin, CallRequestFunctionDelegatePin);
	check(bConnectedDelegatePins)
}

void UK2BeamNode_ApiRequest::EnterBeamFlowModeImpl()
{
	RemoveAllPins(this, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete});
	CreateBeamFlowModePins(GetResponseClass());
}

void UK2BeamNode_ApiRequest::ExitBeamFlowModeImpl()
{
	const auto RequestFunction = GetApiClass()->FindFunctionByName(GetRequestFunctionName());
	RemoveAllPins(this, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete, OP_ExecuteRequest_Response, OP_ExecuteRequest_Error});
	ParseFunctionForNodeInputPins(this, RequestFunction, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete}, true);
}
#undef LOCTEXT_NAMESPACE
