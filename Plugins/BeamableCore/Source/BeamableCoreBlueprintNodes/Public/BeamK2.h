#pragma once
#include "K2Node_AddDelegate.h"
#include "K2Node_BreakStruct.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_EnumEquality.h"
#include "K2Node_Event.h"
#include "K2Node_IfThenElse.h"
#include "K2Node_MakeArray.h"
#include "K2Node_RemoveDelegate.h"
#include "K2Node_SwitchEnum.h"
#include "K2Node_SwitchName.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "BeamK2"


class UK2Node_ClearDelegate;

namespace BeamK2
{
	const FName MD_BeamFlowNode = FName(TEXT("BeamFlowNode"));
	const FName MD_BeamFlowFunction = FName(TEXT("BeamFlowFunction"));
	const FName MD_BeamOptionalType = FName(TEXT("BeamOptionalType"));
	const FName MD_BeamOperation_MultiUser = FName(TEXT("BeamOperationMultiUser"));


	/**
	 * @brief For each of the custom node start pins, find all the execution flow nodes from the custom node's starting pin forward.
	 * Also, builds a list if there are events connected to any function node (or specific ones if RelevantEventSpawningFunctionNames.Num() > 0)
	 *
	 * The algorithm is as follows ---- For every given CustomNodeStartPins:
	 *   - From the starting pin, get all execution flow nodes that flow from that pin and add them to an Expand Queue.
	 *     - If any of these execution flow nodes are CallFunction nodes whose function matches the names in RelevantEventSpawningFunctionNames, check if they have input Delegate pins.
	 *     - If they do, add the event node connected to them to an ParsingEvent Queue.
	 *   - While there are unparsed ParsingEvents, get all execution flow nodes that flow from that pin and add them to an Expand Events Queue.
	 *     - While doing this, also check these execution flow nodes for relevant function names and whether or not they have delegates on them.
	 *     - If they do, enqueue them in the ParsingEvent Queue.
	 *   - Then, while there are unexpanded nodes in the Expand Queue:
	 *     - Grab all their input pins and follow them backward until you hit node with meta=BeamFlowFunction.
	 *     - Add all not-yet-seen nodes to the PerPinForwardFlow except ones having the meta flag: BeamFlowFunction.
	 *   - Do the same as above for the Expand Events Queue except all the nodes spawning off of events are placed in PerPinConnectedEventFlows. 
	 *
	 * The entire point of this is to allow us to batch replace connections on all nodes in a "flow" with ReplaceConnectionsOnGraphFlow.
	 */
	void GetPerBeamFlowNodes(const FKismetCompilerContext& CompilerContext,
	                         const UEdGraphNode* CustomNode, const TArray<UEdGraphPin*>& CustomNodeStartPins,
	                         const TArray<FName> RelevantEventSpawningFunctionNames, TArray<TArray<UEdGraphNode*>>& PerPinForwardFlow, TArray<TArray<UEdGraphNode*>>& PerPinConnectedEventFlows);


	/**
	 * @brief On each NodeToCorrect, replaces each input pin that is connected to a pin in the "From" list with the Pin in the "To" list at the same idx (parallel lists).
	 */
	void ReplaceConnectionsOnBeamFlow(const TArray<UEdGraphNode*>& NodesToCorrect, const TArray<UEdGraphPin*>& From, const TArray<UEdGraphPin*>& To);


	/**
	 * @brief Utility that creates a correctly configured BreakStruct not for a given UStruct.
	 */
	UK2Node_BreakStruct* CreateBreakStructNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
	                                           UScriptStruct* const StructToBreak, UEdGraphPin* StructInputPin);

	/**
	 * @brief Utility that creates a correctly configured Make Array node with the number of input pins created equal to PinCount.
	 */
	UK2Node_MakeArray* CreateMakeArrayNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, int PinCount);

	/**
	 * @brief Utility that creates a correctly configured SwitchEnum node following the given "ExecFlowPin" and switching on the given "SwitchOnValuePin".
	 */
	UK2Node_SwitchEnum* CreateSwitchEnumNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema, UEnum* const Enum,
	                                         UEdGraphPin* ExecFlowPin, UEdGraphPin* SwitchOnValuePin);

	/**
	 * @brief Utility that creates a correctly configured SwitchString node following the given "ExecFlowPin" and switching on the given "SwitchOnValuePin".
	 */
	UK2Node_SwitchName* CreateSwitchNameNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema, TArray<FName> const StringOptions,
	                                         UEdGraphPin* ExecFlowPin, UEdGraphPin* SwitchOnValuePin);

	/**
	 * Create a Dynamic Cast Node to cast generic objects.
	 *
	 * @param TargetClass: The UClass* result after the cast.
	 */
	UK2Node_DynamicCast* CreateDynamicCastNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UClass* TargetClass);

	/**
	 * @brief Utility that creates and configures an EnumEquality node of the given "EnumToCompareType" to compare "EnumToCompareAgainst" against "CompareAgainstPin".
	 */
	UK2Node_EnumEquality* CreateEnumEqualityAgainstDefault(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
	                                                       const UEnum* EnumToCompareType, const int64 EnumToCompareAgainst, UEdGraphPin* const CompareAgainstPin);

	/**
	 * @brief Utility that creates and configures an IfThenElse node to run with the given condition.
	 */
	UK2Node_IfThenElse* CreateIfThenElseNodeAgainstCondition(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
	                                                         UEdGraphPin* const ExecPin, UEdGraphPin* ConditionPin);

	/**
	 * @brief Utility that creates a correctly configured Event pin for a give FProperty
	 */
	UEdGraphPin* CreateEventPinFromProperty(UEdGraphNode* Node, const FProperty* Property);

	/**
	 * @brief Utility that creates a correctly configured Event pin as Execute pin for a give FProperty
	 */
	TMap<UEdGraphPin*, TArray<UEdGraphPin*>> CreateExecutePinFromEventProperty(UEdGraphNode* Node, const FMulticastDelegateProperty* Property);

	/**
	 * @brief Utility that creates a correctly configured event node for the given delegate name.
	 */
	UK2Node_Event* CreateEventNodeForDelegate(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const FString& DelegateName);

	/**
	 * @brief Utility that moves a pin with PinName from the CustomNode to a pin with that same name in TargetNode. 
	 */
	void MoveWrappedPin(const UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, const UEdGraphNode* TargetNode, const FName& PinName);

	/**
	 * @brief Utility that connects and checks both of the True and False pins to the respective output pins of the given IfThenElse Node.
	 */
	void ConnectIfThenElseNodeOutputs(FKismetCompilerContext& CompilerContext, UEdGraphPin* const TruePin, UEdGraphPin* const FalsePin, const UK2Node_IfThenElse* IfThenElseNode);

	/**
	 * @brief   Utility that creates a AddDelegate node targeting a specific FMulticastDelegate. 	
	 */
	UK2Node_AddDelegate* CreateAddDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty);

	/**
	 * @brief   Utility that creates a RemoveDelegate node targeting a specific FMulticastDelegate. 	
	 */
	UK2Node_RemoveDelegate* CreateRemoveDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty);

	/**
	 * @brief   Utility that creates a ClearDelegate node targeting a specific FMulticastDelegate. 	
	 */
	UK2Node_ClearDelegate* CreateClearDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty);


	/**
	 * @brief Utility that creates a call function node targeting a specific UClass's UFunction. 	 
	 */
	UK2Node_CallFunction* CreateCallFunctionNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FName FunctionName, UClass* UClass);


	template <typename T>
	UFunction* FindFunctionByName(FName FunctionName)
	{
		static_assert(TIsDerivedFrom<T, UObject>::Value);

		auto Func = T::StaticClass()->FindFunctionByName(FunctionName);
		// UE Commented on this --- no clue what it means: "If the generated class is not up to date, use the skeleton's class function to create pins:"
		Func = FBlueprintEditorUtils::GetMostUpToDateFunction(Func);
		return Func;
	}

	/**
	 * @brief Typedef for the Predicate used by ParseFunctionForNodeInputPins
	 */
	typedef bool (*CheckParamIsValidForNodePredicate)(const UEdGraphNode*, const FProperty*);
	typedef TFunctionRef<bool (const UEdGraphNode*, const UEdGraphPin*)> PinPredicate;
	/**
	 * @brief Given a custom node and a UFUNCTION goes through the list of parameters of that function and, if that param passes the Predicate,
	 * creates a pin for it and adds the pin name to the WrappedPinNames array.
	 */
	void ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& WrappedPinNames,
	                                   const CheckParamIsValidForNodePredicate Predicate);

	/**
	 * @brief Given a custom node and a UFUNCTION goes through the list of parameters of that function and, if that param passes the Predicate,
	 * creates a pin for it and adds the pin name to the WrappedPinNames array.
	 */
	void ParseFunctionForNodePins(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& InputWrappedPinNames, TArray<FString>& OutputWrappedPinNames,
	                              const CheckParamIsValidForNodePredicate Predicate);

	/**
	 * @brief Given a custom node and a UFUNCTION goes through the list of parameters of that function and, if that param passes the Predicate,
	 * creates a output pin for it and adds array output as a ARRAY ELEMENT.
	 */
	void ParseFunctionForNodeOutputPinsArrayElement(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& OutputWrappedPinNames);

	/**
	* @brief  Given a custom node and a UFUNCTION, tries to create pins for all of the pins given.
	 */
	void ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, const TArray<FName> PinsToAdd, bool bFailIfNotFound = false);

	/**
	 * @brief Goes through the list of NodesToSearchIn and see if any of their pins are connected to any of the InvalidPins. If so, adds the respective InvalidPinErrorMessages
	 * to the CompilerContext's message log.
	 */
	void ValidateOutputPinUsage(const FKismetCompilerContext& CompilerContext, const TArray<UEdGraphPin*>& InvalidPins, const TArray<FString>& InvalidPinErrorMessages,
	                            const TArray<UEdGraphNode*>& NodesToSearchIn);

	/**
	 * @brief Checks if the given graph is a Macro or the default EventGraph.	  
	 */
	bool IsMacroOrEventGraph(const UEdGraph* Graph);

	/**
	 * @brief Removes all pins (breaking their links). 
	 */
	void RemoveAllPins(UEdGraphNode* CustomNode, const TArray<FName> PinsToRemove);

	/**
	 * @brief Enforces that a pin exists. If it is already there, recreates it (recreates the connections it had).
	  
	 */
	UEdGraphPin* EnforcePinExistence(UEdGraphNode* CustomNode, EEdGraphPinDirection Direction, FName Category, FName Name, FString Tooltip,
	                                 UEdGraphNode::FCreatePinParams Params = {}, UObject* CatSubObject = nullptr);

	/**
	 * @brief Gets an array pin with the given name. If "!bIsArray", then create nodes to index into the array and return the element at "DefaultElementIdx".
	 */
	UEdGraphPin* ExpandIntoArrayOrRegularIntermediatePin(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_Event* IntermediateEventNode,
	                                                     const FName PinName, bool bIsArray, int DefaultElementIdx = 0);

	void RemoveAllPinsExcept(UEdGraphNode* CustomNode, PinPredicate ExceptPins);
	void RemoveAllPinsExcept(UEdGraphNode* CustomNode, PinPredicate ExceptPins, TArray<TArray<UEdGraphPin*>>& Connections);

	void RemoveAllPins(UEdGraphNode* CustomNode, const TArray<FName> PinsToRemove, TArray<TArray<UEdGraphPin*>>& Connections);

	/**
	 * @brief Connects a subsystem's GetSelf call to a CallFunction node that is pointing to a function of that Subsystem.	  
	 */
	void SetUpPinsFunctionToOwnerSubsystem(const UK2Node_CallFunction* CallGetSubsystem, const UK2Node_CallFunction* CallRequestFunction);
}
#undef LOCTEXT_NAMESPACE
