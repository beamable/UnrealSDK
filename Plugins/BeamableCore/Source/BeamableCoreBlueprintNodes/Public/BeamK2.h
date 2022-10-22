#pragma once
#include "K2Node_Event.h"
#include "KismetCompiler.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "BeamK2"

class UK2Node_MakeArray;

namespace BeamK2
{
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
	 *     - Grab all their input pins and follow them backward until you hit node with meta=BeamFlowStart.
	 *     - Add all not-yet-seen nodes to the PerPinForwardFlow except ones having the meta flag: BeamFlowStart.
	 *   - Do the same as above for the Expand Events Queue except all the nodes spawning off of events are placed in PerPinConnectedEventFlows. 
	 *
	 * The entire point of this is to allow us to batch replace connections on all nodes in a "flow" with ReplaceConnectionsOnGraphFlow.
	 */
	static void GetPerBeamFlowNodes(const FKismetCompilerContext& CompilerContext,
	                                const UEdGraphNode* CustomNode, const TArray<UEdGraphPin*>& CustomNodeStartPins,
	                                const TArray<FName> RelevantEventSpawningFunctionNames, TArray<TArray<UEdGraphNode*>>& PerPinForwardFlow, TArray<TArray<UEdGraphNode*>>& PerPinConnectedEventFlows);


	/**
	 * @brief On each NodeToCorrect, replaces each input pin that is connected to a pin in the "From" list with the Pin in the "To" list at the same idx (parallel lists).
	 */
	static void ReplaceConnectionsOnBeamFlow(const TArray<UEdGraphNode*>& NodesToCorrect, const TArray<UEdGraphPin*>& From, const TArray<UEdGraphPin*>& To);

	/**
	 * @brief Utility that creates a correctly configured Make Array node with the number of input pins created equal to PinCount.
	 */
	static UK2Node_MakeArray* CreateMakeArrayNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, int PinCount);

	/**
	 * @brief Utility that creates a correctly configured event node for the given delegate name.
	 */
	static UK2Node_Event* CreateEventNodeForDelegate(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const FString& DelegateName);

	/**
	 * @brief Utility that moves a pin with PinName from the CustomNode to a pin with that same name in TargetNode. 
	 */
	static void MoveWrappedPin(const UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, const UEdGraphNode* TargetNode, const FName& PinName);

	/**
	 * @brief Utility that creates a call function node targeting a specific UClass's UFunction. 	 
	 */
	static UK2Node_CallFunction* CreateCallFunctionNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FName FunctionName, UClass* UClass);


	template <typename T>
	static UFunction* FindFunctionByName(FName FunctionName)
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
	/**
	 * @brief Given a custom node and a UFUNCTION goes through the list of parameters of that function and, if that param passes the Predicate,
	 * creates a pin for it and adds the pin name to the WrappedPinNames array.
	 */
	static void ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& WrappedPinNames,
	                                          const CheckParamIsValidForNodePredicate Predicate);

	/**
	* @brief  Given a custom node and a UFUNCTION, tries to create pins for all of the pins given.
	 */
	static void ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, const TArray<FName> PinsToAdd, bool bFailIfNotFound = false);

	/**
	 * @brief Goes through the list of NodesToSearchIn and see if any of their pins are connected to any of the InvalidPins. If so, adds the respective InvalidPinErrorMessages
	 * to the CompilerContext's message log.
	 */
	static void ValidateOutputPinUsage(const FKismetCompilerContext& CompilerContext, const TArray<UEdGraphPin*>& InvalidPins, const TArray<FString>& InvalidPinErrorMessages,
	                                   const TArray<UEdGraphNode*>& NodesToSearchIn);

	/**
	 * @brief Checks if the given graph is a Macro or the default EventGraph.	  
	 */
	static bool IsMacroOrEventGraph(const UEdGraph* Graph);

	/**
	 * @brief Removes all pins (breaking their links). 
	 */
	static void RemoveAllPins(UEdGraphNode* CustomNode, const TArray<FName> PinsToRemove);
}
#undef LOCTEXT_NAMESPACE
