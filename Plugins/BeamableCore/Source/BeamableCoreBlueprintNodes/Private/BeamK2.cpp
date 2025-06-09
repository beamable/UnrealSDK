#include "BeamK2.h"


#include "K2Node_BreakStruct.h"
#include "K2Node_CallFunction.h"
#include "K2Node_ClearDelegate.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_EnumEquality.h"
#include "K2Node_GetArrayItem.h"
#include "K2Node_MakeArray.h"
#include "K2Node_SwitchInteger.h"
#include "K2Node_SwitchName.h"
#include "K2Node_SwitchString.h"
#include "KismetCompiler.h"

#define BEAM_K2_LOG_VERBOSITY Verbose
//#define BEAM_K2_ADD_NOTES_TO_FLOW_NODES

#define LOCTEXT_NAMESPACE "BeamK2"

void BeamK2::GetPerBeamFlowNodes(const FKismetCompilerContext& CompilerContext, const UEdGraphNode* CustomNode,
                                 const TArray<UEdGraphPin*>& CustomNodeStartPins, const TArray<FName> RelevantEventSpawningFunctionNames,
                                 TArray<TArray<UEdGraphNode*>>& PerPinForwardFlow, TArray<TArray<UEdGraphNode*>>& PerPinConnectedEventFlows)
{
	check(CustomNode != nullptr)
	check(CustomNodeStartPins.Num() > 0)

	PerPinForwardFlow = TArray<TArray<UEdGraphNode*>>{};

	// Here we do this for all the nodes that are part of the sub-chain of connections we moved to the intermediate event.
	TArray<UEdGraphNode*> ToExpand;
	TArray<UEdGraphNode*> ToExpandEvents;

	TArray<UEdGraphNode*> ToParse;
	TArray<UEdGraphNode*> ParsedNodes;

	TArray<UEdGraphNode*> ToParseEvents;
	TArray<UEdGraphNode*> ParsedNodesEvents;
	for (const auto GraphStartPin : CustomNodeStartPins)
	{
		// We only allow getting sub-graphs with this if you start from exec pins.		
		check(GraphStartPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec)
		const auto FlowName = CustomNode->GetName() + TEXT("_") + (GraphStartPin->GetDisplayName().ToString().IsEmpty() ? "Synchronous Flow" : GraphStartPin->GetDisplayName().ToString());

		// Add the nodes connected to this starting pin to the Parse queue		
		for (const auto LinkedTo : GraphStartPin->LinkedTo)
		{
			ToParse.Add(LinkedTo->GetOwningNode());
		}

		// Parse this initial list of nodes, finding all events connected to relevant functions.		
		while (ToParse.Num() > 0)
		{
			const auto Parsing = ToParse[0];
			ToParse.RemoveAt(0);

			if (ParsedNodes.Contains(Parsing))
				continue;

			ParsedNodes.Add(Parsing);
			ToExpand.Add(Parsing);
			UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s - Storing Node to Expand %s"), *FlowName, *Parsing->GetDescriptiveCompiledName())

			if (Parsing == CustomNode)
				continue;

			// We add the next 
			const auto OutputPins = Parsing->Pins.FilterByPredicate([=](const UEdGraphPin* P)
			{
				UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s - Looking at Pin %s to follow into  %s to Parse List. PinCategory=%s, Dir=%s"),
				       *FlowName, *P->PinName.ToString(), *Parsing->GetDescriptiveCompiledName(),
				       *P->PinType.PinCategory.ToString(), *UEnum::GetValueAsString(P->Direction))
				return P->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec; // P->PinName.ToString().StartsWith("On");
			});
			for (const auto& OnCallbackPin : OutputPins)
			{
				for (const auto LinkedTo : OnCallbackPin->LinkedTo)
				{
					const auto FollowNode = LinkedTo->GetOwningNode();
					ToParse.Add(FollowNode);
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Following Pin %s -> %s into Node %s to Parse List"),
					       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *OnCallbackPin->PinName.ToString(), *LinkedTo->PinName.ToString(),
					       *FollowNode->GetDescriptiveCompiledName())
				}
			}

			// If we are parsing a node that has an input event that it will call...
			for (const auto DelegatePin : Parsing->Pins.FilterByPredicate([&RelevantEventSpawningFunctionNames](const UEdGraphPin* P)
			{
				if (P)
				{
					const auto AsCallFunctionNode = Cast<UK2Node_CallFunction>(P->GetOwningNode());

					const auto bIsRelevantInputPin = P->Direction == EGPD_Input &&
						(P->PinType.PinCategory == UEdGraphSchema_K2::PC_Delegate || P->PinType.PinCategory == UEdGraphSchema_K2::PC_MCDelegate);

					if (!AsCallFunctionNode || !AsCallFunctionNode->GetTargetFunction())
						return false;

					const auto bIsRelevantFunction = RelevantEventSpawningFunctionNames.Num() == 0 || RelevantEventSpawningFunctionNames.Contains(AsCallFunctionNode->GetFunctionName());
					const auto bIsAFlowFunction = AsCallFunctionNode->GetTargetFunction()->HasMetaData(MD_BeamFlowFunction);
					return bIsRelevantInputPin && (bIsRelevantFunction || bIsAFlowFunction);
				}

				return false;
			}))
			{
				for (const auto EventNodePin : DelegatePin->LinkedTo)
				{
					const auto EventNode = EventNodePin->GetOwningNode();
					ToParseEvents.Add(EventNode);
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Adding Event Node %s to Parse List"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
					       *EventNode->GetDescriptiveCompiledName())
				}
			}
		}

		// Add found as notes
		for (const auto& Expand : ToExpand)
			UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Found Node %s while following this Beam Flow"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
		       *Expand->GetDescriptiveCompiledName())

		// // Parse all event flows that are connected to relevant function's delegates
		while (ToParseEvents.Num() > 0)
		{
			const auto Parsing = ToParseEvents[0];
			ToParseEvents.RemoveAt(0);

			if (ParsedNodesEvents.Contains(Parsing))
				continue;

			ParsedNodesEvents.Add(Parsing);
			ToExpandEvents.Add(Parsing);

			// We add the next 
			const auto OutputPins = Parsing->Pins.FilterByPredicate([=](const UEdGraphPin* P)
			{
				UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s - Looking at Pin %s to follow into  %s to Parse List. PinCategory=%s, Dir=%s"),
				       *FlowName, *P->PinName.ToString(), *Parsing->GetDescriptiveCompiledName(),
				       *P->PinType.PinCategory.ToString(), *UEnum::GetValueAsString(P->Direction))
				return P->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec; // P->PinName.ToString().StartsWith("On");
			});
			for (const auto& OnCallbackPin : OutputPins)
			{
				for (const auto LinkedTo : OnCallbackPin->LinkedTo)
				{
					const auto FollowNode = LinkedTo->GetOwningNode();
					ToParseEvents.Add(FollowNode);
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Following Pin %s -> %s into Node %s to Parse List"),
					       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *OnCallbackPin->PinName.ToString(), *LinkedTo->PinName.ToString(),
					       *FollowNode->GetDescriptiveCompiledName())
				}
			}

			// If we are parsing a node that has an input event that it will call...
			for (const auto DelegatePin : Parsing->Pins.FilterByPredicate([&RelevantEventSpawningFunctionNames, &CompilerContext, FlowName, GraphStartPin](const UEdGraphPin* P)
			{
				const auto AsCallFunctionNode = Cast<UK2Node_CallFunction>(P->GetOwningNode());
				const auto bIsRelevantInputPin = P->Direction == EGPD_Input && P->PinType.PinCategory == UEdGraphSchema_K2::PC_Delegate;

				if (P->PinType.PinCategory == UEdGraphSchema_K2::PC_MCDelegate)
				{
					CompilerContext
						.MessageLog
						.Warning(
							*FString::Printf(TEXT("@@ | %s - You can't use BeamFlow pins in Multi-cast Delegates in node @@!"), *FlowName),
							GraphStartPin->GetOwningNode(),
							P->GetOwningNode()
						);
					return false;
				}

				if (!AsCallFunctionNode)
					return false;


				const auto bIsRelevantFunction = RelevantEventSpawningFunctionNames.Num() == 0 || RelevantEventSpawningFunctionNames.Contains(AsCallFunctionNode->GetFunctionName());
				const auto bIsAFlowFunction = AsCallFunctionNode->GetTargetFunction()->HasMetaData(MD_BeamFlowFunction);
				return bIsRelevantInputPin && (bIsRelevantFunction || bIsAFlowFunction);
			}))
			{
				for (const auto EventNodePin : DelegatePin->LinkedTo)
				{
					const auto EventNode = EventNodePin->GetOwningNode();
					ToParseEvents.Add(EventNode);
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Adding Event %s to Parse from Node %s"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
					       *EventNode->GetDescriptiveCompiledName(),
					       *Parsing->GetDescriptiveCompiledName())
				}
			}
		}

		// Add logs as notes
		for (const auto& Expand : ToExpand)
			UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Found Node %s while following this Beam Flow"),
		       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *Expand->GetDescriptiveCompiledName())

		// We'll store all the nodes that are considered to be in this flow here
		TArray<UEdGraphNode*> FlowNodes;

		// While we have nodes in this flow that we need to expand, continue doing so...		
		while (ToExpand.Num() > 0)
		{
			const auto ExpandingNode = ToExpand[0];
			ToExpand.RemoveAt(0);

			// First, we simply add the expanding node to the one in the flow --- we don't add duplicates.
			if (!FlowNodes.Contains(ExpandingNode))
			{
				FlowNodes.Add(ExpandingNode);
				UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Adding Node %s to this Beam Flow"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
				       *ExpandingNode->GetDescriptiveCompiledName())
			}

			// Then, we look backwards through all input pins so that we add all Pure Nodes (nodes that don't have an execution pin) that are considered to be in this flow into the list of nodes to expand.
			for (const auto ConnectedPin : ExpandingNode->Pins.FilterByPredicate([](const UEdGraphPin* P)
			{
				return P->Direction == EGPD_Input && P->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec;
			}))
			{
				for (const auto LinkedTo : ConnectedPin->LinkedTo)
				{
					// Get the node we are connected to
					const auto LinkedToNode = LinkedTo->GetOwningNode();

					// We don't ever backfill past ourselves					
					const auto bIsNotSelf = LinkedToNode != CustomNode;

					// We don't cyclically expand the node if we have already added it to the list of nodes in this flow.
					const auto NotCyclical = !FlowNodes.Contains(LinkedToNode);

					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Trying to Backfill node %s connected to input pin %s into this Beam Flow -- %s, %s"),
					       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *LinkedToNode->GetDescriptiveCompiledName(), *ConnectedPin->GetName(),
					       bIsNotSelf ? TEXT("true") : TEXT("false"), NotCyclical ? TEXT("true") : TEXT("false"))

					// If we should expand this node, let's just add it to the list of nodes to expand.										
					if (bIsNotSelf && NotCyclical)
					{
						ToExpand.Add(LinkedToNode);
						UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Backfilling node %s connected to input pin %s into this Beam Flow"),
						       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *LinkedToNode->GetDescriptiveCompiledName(), *ConnectedPin->GetName())
					}
				}
			}
		}
		// Add logs as notes			
		PerPinForwardFlow.Add(FlowNodes);
		for (const auto& FlowNode : FlowNodes)
		{
#ifdef BEAM_K2_ADD_NOTES_TO_FLOW_NODES
			CompilerContext.MessageLog.Note(*FString::Printf(TEXT("@@ | %s - Found Node @@ while following this Beam Flow"), *FlowName), GraphStartPin->GetOwningNode(), FlowNode);
#endif
			UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Found Node %s while following this Beam Flow"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
			       *FlowNode->GetDescriptiveCompiledName())
		}

		// We'll store all the nodes that are considered to be in this flow's Events here
		TArray<UEdGraphNode*> EventsFlowNodes;
		// While we have nodes on event flows that we need to expand (backfill nodes connected to input pins into the flow), continue doing so...
		while (ToExpandEvents.Num() > 0)
		{
			const auto ExpandingNode = ToExpandEvents[0];
			ToExpandEvents.RemoveAt(0);

			// First, we simply add the expanding node to the one in the flow --- we don't add duplicates.
			if (!EventsFlowNodes.Contains(ExpandingNode))
			{
				EventsFlowNodes.Add(ExpandingNode);
				UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Adding Node %s from an Event node while following this Beam Flow"),
				       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName,
				       *ExpandingNode->GetDescriptiveCompiledName())
			}

			// Then, we look backwards through all input pins so that we add all Pure Nodes (nodes that don't have an execution pin) that are considered to be in this flow into the list of nodes to expand.
			for (const auto ConnectedPin : ExpandingNode->Pins.FilterByPredicate([](const UEdGraphPin* P)
			{
				return P->Direction == EGPD_Input && P->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec;
			}))
			{
				for (const auto LinkedTo : ConnectedPin->LinkedTo)
				{
					// Get the node we are connected to
					const auto LinkedToNode = LinkedTo->GetOwningNode();

					// We don't ever backfill past ourselves					
					const auto bIsNotSelf = LinkedToNode != CustomNode;

					// We don't cyclically expand the node if we have already added it to the list of nodes in this flow.
					const auto NotCyclical = !EventsFlowNodes.Contains(LinkedToNode);

					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Trying to Backfill node %s connected to input pin %s into this Beam Flow -- %s, %s"),
					       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *LinkedToNode->GetDescriptiveCompiledName(), *ConnectedPin->GetName(),
					       bIsNotSelf ? TEXT("true") : TEXT("false"), NotCyclical ? TEXT("true") : TEXT("false"))

					// If we should expand this node, let's just add it to the list of nodes to expand.										
					if (bIsNotSelf && NotCyclical)
					{
						ToExpandEvents.Add(LinkedToNode);
						UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Backfilling node %s connected to input pin %s into this Beam Flow"),
						       *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(), *FlowName, *LinkedToNode->GetDescriptiveCompiledName(), *ConnectedPin->GetName())
					}
				}
			}
		}
		PerPinConnectedEventFlows.Add(EventsFlowNodes);
		for (const auto& FlowNode : EventsFlowNodes)
		{
#ifdef BEAM_K2_ADD_NOTES_TO_FLOW_NODES
			CompilerContext.MessageLog.Note(*FString::Printf(TEXT("@@ | %s - Found Node @@ while following Events passed in via this Beam Flow"), *FlowName), GraphStartPin->GetOwningNode(), FlowNode);
#endif
			UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("%s | %s - Found Node %s while following Events passed in via this Beam Flow"), *GraphStartPin->GetOwningNode()->GetDescriptiveCompiledName(),
			       *FlowName,
			       *FlowNode->GetDescriptiveCompiledName())
		}
	}
}

void BeamK2::ReplaceConnectionsOnBeamFlow(const TArray<UEdGraphNode*>& NodesToCorrect, const TArray<UEdGraphPin*>& From, const TArray<UEdGraphPin*>& To)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	for (const auto GraphNode : NodesToCorrect)
	{
		for (const auto GraphPin : GraphNode->Pins)
		{
			for (int32 i = 0; i < From.Num(); i++)
			{
				const auto RelevantPin = From[i];

				if (!GraphPin)
				{
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("Graph Pin was null, skipping it during %s. You should never see this!"),
					       *GraphNode->GetDescriptiveCompiledName())
					continue;
				}
				if (!RelevantPin)
				{
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("Relevant Pin Was null, skipping it during %s->%s node. You should never see this!"),
					       *GraphNode->GetDescriptiveCompiledName(), *GraphPin->PinName.ToString())
					continue;
				}


				UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("Comparing Node's %s Pin %s connected to relevant pin %s = %s"),
				       *GraphNode->GetDescriptiveCompiledName(), *GraphPin->PinName.ToString(), *RelevantPin->PinName.ToString(),
				       GraphPin->LinkedTo.Contains(RelevantPin) ? TEXT("true") : TEXT("false"))
				if (GraphPin->LinkedTo.Contains(RelevantPin))
				{
					UE_LOG(LogTemp, BEAM_K2_LOG_VERBOSITY, TEXT("Correcting Node's %s Pin %s connected to relevant pin %s"),
					       *GraphNode->GetDescriptiveCompiledName(), *GraphPin->PinName.ToString(), *RelevantPin->PinName.ToString())
					GraphPin->BreakLinkTo(RelevantPin);
					const auto bConnectedEventPins = K2Schema->TryCreateConnection(GraphPin, To[i]);
					checkf(bConnectedEventPins, TEXT("FROM_PIN_NAME=%s, TO_PIN_NAME= %s"), *GraphPin->GetName(), *To[i]->GetName());
				}
			}
		}
	}
}

UK2Node_BreakStruct* BeamK2::CreateBreakStructNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
                                                   UScriptStruct* const StructToBreak, UEdGraphPin* StructInputPin)
{
	UK2Node_BreakStruct* BreakStructNode = CompilerContext.SpawnIntermediateNode<UK2Node_BreakStruct>(CustomNode, SourceGraph);
	BreakStructNode->StructType = StructToBreak;
	BreakStructNode->bMadeAfterOverridePinRemoval = true;
	BreakStructNode->AllocateDefaultPins();

	// Connect the Result pin to the break pin	
	const auto bConnectedBreakPins = K2Schema->TryCreateConnection(StructInputPin, BreakStructNode->FindPin(StructToBreak->GetFName()));
	check(bConnectedBreakPins)

	return BreakStructNode;
}

UK2Node_MakeArray* BeamK2::CreateMakeArrayNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, int PinCount)
{
	UK2Node_MakeArray* ArrayNode = CompilerContext.SpawnIntermediateNode<UK2Node_MakeArray>(CustomNode, SourceGraph);
	ArrayNode->NumInputs = PinCount;
	ArrayNode->AllocateDefaultPins();
	return ArrayNode;
}


UK2Node_SwitchEnum* BeamK2::CreateSwitchEnumNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema, UEnum* const Enum,
                                                 UEdGraphPin* ExecFlowPin, UEdGraphPin* SwitchOnValuePin)
{
	UK2Node_SwitchEnum* SwitchEnum = CompilerContext.SpawnIntermediateNode<UK2Node_SwitchEnum>(CustomNode, SourceGraph);

	// This is the equivalent of the SetEnum call --- we can't use it since it's not exposed for other modules. It seems unclear as to why that wouldn't be accessible... 
	{
		SwitchEnum->Enum = Enum;

		// regenerate enum name list
		SwitchEnum->EnumEntries.Empty();
		SwitchEnum->EnumFriendlyNames.Empty();

		if (Enum)
		{
			if ((Enum != NULL) && Enum->HasAnyFlags(RF_NeedLoad))
			{
				Enum->GetLinker()->Preload(Enum);
			}
			Enum->ConditionalPostLoad();

			for (int32 EnumIndex = 0; EnumIndex < Enum->NumEnums() - 1; ++EnumIndex)
			{
				bool const bShouldBeHidden = Enum->HasMetaData(TEXT("Hidden"), EnumIndex) || Enum->HasMetaData(TEXT("Spacer"), EnumIndex);
				if (!bShouldBeHidden)
				{
					FString const EnumValueName = Enum->GetNameStringByIndex(EnumIndex);
					SwitchEnum->EnumEntries.Add(FName(*EnumValueName));

					FText EnumFriendlyName = Enum->GetDisplayNameTextByIndex(EnumIndex);
					SwitchEnum->EnumFriendlyNames.Add(EnumFriendlyName);
				}
			}
		}
	}
	SwitchEnum->bHasDefaultPin = false;
	SwitchEnum->AllocateDefaultPins();
	K2Schema->TryCreateConnection(SwitchEnum->GetSelectionPin(), SwitchOnValuePin);
	K2Schema->TryCreateConnection(ExecFlowPin, SwitchEnum->GetExecPin());
	return SwitchEnum;
}

UK2Node_SwitchName* BeamK2::CreateSwitchNameNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema, TArray<FName> const StringOptions,
                                                 UEdGraphPin* ExecFlowPin, UEdGraphPin* SwitchOnValuePin)
{
	UK2Node_SwitchName* Switch = CompilerContext.SpawnIntermediateNode<UK2Node_SwitchName>(CustomNode, SourceGraph);

	// This is the equivalent of the SetEnum call --- we can't use it since it's not exposed for other modules. It seems unclear as to why that wouldn't be accessible... 
	Switch->PinNames = StringOptions;
	Switch->bHasDefaultPin = true;

	Switch->AllocateDefaultPins();
	K2Schema->TryCreateConnection(Switch->GetSelectionPin(), SwitchOnValuePin);
	K2Schema->TryCreateConnection(ExecFlowPin, Switch->GetExecPin());
	return Switch;
}

UK2Node_DynamicCast* BeamK2::CreateDynamicCastNode(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UClass* TargetClass)
{
	UK2Node_DynamicCast* CastNode = CompilerContext.SpawnIntermediateNode<UK2Node_DynamicCast>(CustomNode, SourceGraph);
	CastNode->TargetType = TargetClass;
	CastNode->AllocateDefaultPins();
	return CastNode;
}

UK2Node_EnumEquality* BeamK2::CreateEnumEqualityAgainstDefault(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
                                                               const UEnum* EnumToCompareType, const int64 EnumToCompareAgainst, UEdGraphPin* const CompareAgainstPin)
{
	UK2Node_EnumEquality* EnumEquality = CompilerContext.SpawnIntermediateNode<UK2Node_EnumEquality>(CustomNode, SourceGraph);
	EnumEquality->AllocateDefaultPins();
	// Connect the Result pin to the break pin
	const auto bConnected = K2Schema->TryCreateConnection(CompareAgainstPin, EnumEquality->FindPin(TEXT("A")));
	check(bConnected)

	// Set the default value of this one to success
	EnumEquality->FindPin(TEXT("B"))->DefaultValue = EnumToCompareType->GetNameStringByValue(EnumToCompareAgainst);

	return EnumEquality;
}

UK2Node_IfThenElse* BeamK2::CreateIfThenElseNodeAgainstCondition(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UEdGraphSchema_K2* K2Schema,
                                                                 UEdGraphPin* const ExecPin, UEdGraphPin* ConditionPin)
{
	UK2Node_IfThenElse* IfThenElseNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(CustomNode, SourceGraph);
	IfThenElseNode->AllocateDefaultPins();
	{
		const auto bConnectedEnumEqualityToCondition = K2Schema->TryCreateConnection(ConditionPin, IfThenElseNode->GetConditionPin());
		check(bConnectedEnumEqualityToCondition)

		const auto bConnectedEvent = K2Schema->TryCreateConnection(ExecPin, IfThenElseNode->GetExecPin());
		check(bConnectedEvent)
	}

	return IfThenElseNode;
}

UEdGraphPin* BeamK2::CreateEventPinFromProperty(UEdGraphNode* Node, const FProperty* Property)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = Node->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Delegate, Property->GetFName());

	const bool _ = K2Schema->ConvertPropertyToPinType(Property, /*out*/ Pin->PinType);

	Pin->PinType.PinCategory = UEdGraphSchema_K2::PC_Delegate;
	Pin->PinType.bIsReference = true;
	Pin->PinType.bIsConst = true;
	K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);

	return Pin;
}

TMap<UEdGraphPin*, TArray<UEdGraphPin*>> BeamK2::CreateExecutePinFromEventProperty(UEdGraphNode* Node, const FMulticastDelegateProperty* Property)
{
	TMap<UEdGraphPin*, TArray<UEdGraphPin*>> PinMap;

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UEdGraphPin* Pin = Node->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, Property->GetFName());

	PinMap.Add(Pin, {});

	// This gives you the function signature that any delegate bound to this must match
	UFunction* SignatureFunction = Property->SignatureFunction;

	if (SignatureFunction)
	{
		for (TFieldIterator<FProperty> It(SignatureFunction); It && (It->PropertyFlags & CPF_Parm); ++It)
		{
			FProperty* Param = *It;

			FString ParamName = Property->GetName() + TEXT(" - ") + Param->GetName();

			UEdGraphPin* ParamPin = Node->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, *ParamName);

			const bool _ = K2Schema->ConvertPropertyToPinType(Param, /*out*/ ParamPin->PinType);

			PinMap[Pin].Add(ParamPin);
		}
	}

	return PinMap;
}


UK2Node_Event* BeamK2::CreateEventNodeForDelegate(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const FString& DelegateName)
{
	// Adds the event node to the graph.
	UK2Node_Event* EventNode = CompilerContext.SpawnIntermediateNode<UK2Node_Event>(Node, SourceGraph);

	// To ensure uniqueness per graph we use the owner custom node's name in this node as well.
	const auto EventNodeName = FString::Printf(TEXT("%sHandler_%s_%s"), *DelegateName, *SourceGraph->GetName(), *Node->GetName());
	EventNode->CustomFunctionName = FName(*EventNodeName);

	// When wrapping a Custom Event node that expects a certain Dynamic Delegate, you need to pass in "DelegateName__DelegateSignature".
	// The line below is from the Input node.
	// 
	//	InputActionEvent->EventReference.SetExternalDelegateMember(FName(TEXT("InputActionHandlerDynamicSignature__DelegateSignature")));
	//
	// This just makes a UK2Node_Event with the signature of the given delegate as the output pins.
	EventNode->EventReference.SetExternalDelegateMember(FName(*FString::Printf(TEXT("%s__DelegateSignature"), *DelegateName)));

	// Calling this builds the node pins correctly based on the given Delegate Signature
	EventNode->AllocateDefaultPins();
	// Return the node
	return EventNode;
}

void BeamK2::MoveWrappedPin(const UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, const UEdGraphNode* TargetNode, const FName& PinName)
{
	const auto WrapperPin = CustomNode->FindPinChecked(PinName);
	const auto TargetPin = TargetNode->FindPinChecked(PinName);
	const auto Moved = CompilerContext.MovePinLinksToIntermediate(*WrapperPin, *TargetPin);
	check(!Moved.IsFatal());
}

void BeamK2::ConnectIfThenElseNodeOutputs(FKismetCompilerContext& CompilerContext, UEdGraphPin* const TruePin, UEdGraphPin* const FalsePin, const UK2Node_IfThenElse* IfThenElseNode)
{
	const auto IntermediateSuccessPin = IfThenElseNode->GetThenPin();
	const auto SuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*TruePin, *IntermediateSuccessPin);
	check(!SuccessFlowMoved.IsFatal());

	const auto IntermediateOthersPin = IfThenElseNode->GetElsePin();
	const auto NonSuccessFlowMoved = CompilerContext.MovePinLinksToIntermediate(*FalsePin, *IntermediateOthersPin);
	check(!NonSuccessFlowMoved.IsFatal());
}

UK2Node_AddDelegate* BeamK2::CreateAddDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty)
{
	auto AddDelegateNode = CompilerContext.SpawnIntermediateNode<UK2Node_AddDelegate>(Node, SourceGraph);

	AddDelegateNode->SetFromProperty(
		MulticastDelegateProperty,
		false,
		MulticastDelegateProperty->GetOwnerClass()
	);

	AddDelegateNode->AllocateDefaultPins();

	return AddDelegateNode;
}

UK2Node_RemoveDelegate* BeamK2::CreateRemoveDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty)
{
	auto RemoveDelegateNode = CompilerContext.SpawnIntermediateNode<UK2Node_RemoveDelegate>(Node, SourceGraph);

	RemoveDelegateNode->SetFromProperty(
		MulticastDelegateProperty,
		false,
		MulticastDelegateProperty->GetOwnerClass()
	);

	RemoveDelegateNode->AllocateDefaultPins();

	return RemoveDelegateNode;
}

UK2Node_ClearDelegate* BeamK2::CreateClearDelegateNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, FMulticastDelegateProperty* MulticastDelegateProperty)
{
	auto ClearDelegateNode = CompilerContext.SpawnIntermediateNode<UK2Node_ClearDelegate>(Node, SourceGraph);

	ClearDelegateNode->SetFromProperty(
		MulticastDelegateProperty,
		false,
		MulticastDelegateProperty->GetOwnerClass()
	);

	ClearDelegateNode->AllocateDefaultPins();

	return ClearDelegateNode;
}


UK2Node_CallFunction* BeamK2::CreateCallFunctionNode(UEdGraphNode* Node, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph,
                                                     FName FunctionName, UClass* UClass)
{
	UK2Node_CallFunction* CallFunctionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(Node, SourceGraph);
	CallFunctionNode->FunctionReference.SetExternalMember(FunctionName, UClass);
	CallFunctionNode->AllocateDefaultPins();
	return CallFunctionNode;
}

void BeamK2::ValidateOutputPinUsage(const FKismetCompilerContext& CompilerContext, const TArray<UEdGraphPin*>& InvalidPins, const TArray<FString>& InvalidPinErrorMessages,
                                    const TArray<UEdGraphNode*>& NodesToSearchIn)
{
	const FString FlowError_InvalidPinUsageInBeamFlow = LOCTEXT("InvalidPinUsageInBeamExecuteNodeFlows_ErrorFollowUp", "Node @@ depends on an disallowed Pin coming from @@!").ToString();

	for (const auto& FlowNode : NodesToSearchIn)
	{
		for (const auto& Pin : FlowNode->Pins)
		{
			for (int32 InvalidPinIdx = 0; InvalidPinIdx < InvalidPins.Num(); InvalidPinIdx++)
			{
				const auto InvalidPin = InvalidPins[InvalidPinIdx];
				if (Pin->LinkedTo.Contains(InvalidPin))
				{
					CompilerContext.MessageLog.Error(*InvalidPinErrorMessages[InvalidPinIdx], FlowNode);
					for (const auto& OutputPin : FlowNode->Pins)
					{
						if (OutputPin->Direction == EGPD_Output && OutputPin->LinkedTo.Num() > 0)
						{
							for (const auto& LinkedTo : OutputPin->LinkedTo)
							{
								const auto Node = LinkedTo->GetOwningNode();
								if (NodesToSearchIn.Contains(Node))
								{
									CompilerContext.MessageLog.Error(*FlowError_InvalidPinUsageInBeamFlow, Node, FlowNode);
								}
							}
						}
					}
				}
			}
		}
	}
}

bool BeamK2::IsMacroOrEventGraph(const UEdGraph* Graph)
{
	// This node expands into event nodes and must be placed in a Ubergraph
	EGraphType const GraphType = Graph->GetSchema()->GetGraphType(Graph);
	const bool bIsCompatible = (GraphType == EGraphType::GT_Ubergraph) || GraphType == GT_Macro;
	return bIsCompatible;
}

void BeamK2::RemoveAllPins(UEdGraphNode* CustomNode, const TArray<FName> PinsToRemove)
{
	TArray<TArray<UEdGraphPin*>> Connections;
	RemoveAllPins(CustomNode, PinsToRemove, Connections);
}

UEdGraphPin* BeamK2::EnforcePinExistence(UEdGraphNode* CustomNode, EEdGraphPinDirection Direction, FName Category, FName Name, FString Tooltip, UEdGraphNode::FCreatePinParams Params,
                                         UObject* CatSubObject)
{
	TArray<UEdGraphPin*> LinkedToPins;
	if (const auto ExistingPin = CustomNode->FindPin(Name))
	{
		if (ExistingPin->LinkedTo.Num() > 0)
		{
			LinkedToPins.Append(ExistingPin->LinkedTo);
		}

		ExistingPin->BreakAllPinLinks();
		CustomNode->RemovePin(ExistingPin);
	}

	UEdGraphPin* CreatedPin;
	if (CatSubObject)
	{
		CreatedPin = CustomNode->CreatePin(Direction, Category, CatSubObject, Name, Params);
		CreatedPin->PinToolTip = Tooltip;
		CreatedPin->PinFriendlyName = FText::FromString(FName::NameToDisplayString(Name.ToString(), false));
	}
	else
	{
		CreatedPin = CustomNode->CreatePin(Direction, Category, Name, Params);
		CreatedPin->PinToolTip = Tooltip;
		CreatedPin->PinFriendlyName = FText::FromString(FName::NameToDisplayString(Name.ToString(), false));
	}

	// Reconnect if they were broken
	for (const auto LinkedToPin : LinkedToPins)
	{
		if (LinkedToPin)
			GetDefault<UEdGraphSchema_K2>()->TryCreateConnection(CreatedPin, LinkedToPin);
	}


	return CreatedPin;
}

UEdGraphPin* BeamK2::ExpandIntoArrayOrRegularIntermediatePin(UEdGraphNode* CustomNode, FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_Event* IntermediateEventNode,
                                                             const FName PinName, bool bIsArray, int DefaultElementIdx)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	auto IntermediateUserSlotPin = IntermediateEventNode->FindPinChecked(PinName);
	if (!bIsArray)
	{
		UK2Node_GetArrayItem* GetArrayItemNode = CompilerContext.SpawnIntermediateNode<UK2Node_GetArrayItem>(CustomNode, SourceGraph);
		GetArrayItemNode->AllocateDefaultPins();

		UEdGraphPin* ArrayPin = GetArrayItemNode->GetTargetArrayPin();
		UEdGraphPin* ArrayGetResultPin = GetArrayItemNode->GetResultPin();
		UEdGraphPin* IndexPin = GetArrayItemNode->GetIndexPin();
		check(ArrayPin && ArrayGetResultPin && IndexPin);

		// Fill in the array index pin default value
		IndexPin->DefaultValue = FString::FromInt(DefaultElementIdx);

		// Connect up the array variable output (CurrentPin) to the array pin					
		if (const bool bSucceeded = K2Schema->TryCreateConnection(IntermediateUserSlotPin, ArrayPin); !bSucceeded)
		{
			CompilerContext.MessageLog.Error(*LOCTEXT("ArrayConnectionFailed", "@@ could not connect array when expanding node!").ToString(), CustomNode);
		}

		// Array element is now the user slot pin
		IntermediateUserSlotPin = ArrayGetResultPin;
	}
	return IntermediateUserSlotPin;
}

void BeamK2::RemoveAllPinsExcept(UEdGraphNode* CustomNode, PinPredicate ExceptPins)
{
	TArray<TArray<UEdGraphPin*>> Connections;
	RemoveAllPinsExcept(CustomNode, ExceptPins, Connections);
}

void BeamK2::RemoveAllPinsExcept(UEdGraphNode* CustomNode, PinPredicate ExceptPins, TArray<TArray<UEdGraphPin*>>& Connections)
{
	for (int i = CustomNode->Pins.Num() - 1; i >= 0; --i)
	{
		const auto Pin = CustomNode->Pins[i];
		if (Pin && !ExceptPins(CustomNode, Pin))
		{
			// Grab all the pins they were linked to.
			UE_LOG(LogTemp, Display, TEXT("Comparing Node's %s Pin %s connected to pins %d"), *CustomNode->GetName(), *Pin->GetName(), Pin->LinkedTo.Num());
			Connections.Add(Pin->LinkedTo);

			// Then break all of them
			Pin->BreakAllPinLinks();
			CustomNode->RemovePin(Pin);
		}
	}
	//CustomNode->GetGraph()->NotifyGraphChanged();
}

void BeamK2::RemoveAllPins(UEdGraphNode* CustomNode, const TArray<FName> PinsToRemove, TArray<TArray<UEdGraphPin*>>& Connections)
{
	for (const auto ToRemove : PinsToRemove)
	{
		if (const auto Pin = CustomNode->FindPin(ToRemove))
		{
			// Grab all the pins they were linked to.
			UE_LOG(LogTemp, Display, TEXT("Comparing Node's %s Pin %s connected to pins %d"), *CustomNode->GetName(), *Pin->GetName(), Pin->LinkedTo.Num());
			Connections.Add(Pin->LinkedTo);

			// Then break all of them
			Pin->BreakAllPinLinks();
			CustomNode->RemovePin(Pin);
		}
	}
}

void BeamK2::SetUpPinsFunctionToOwnerSubsystem(const UK2Node_CallFunction* CallGetSubsystem, const UK2Node_CallFunction* CallRequestFunction)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const auto SubsystemReturnPin = CallGetSubsystem->GetReturnValuePin();
	const auto RequestFunctionSelfPin = K2Schema->FindSelfPin(*CallRequestFunction, EGPD_Input);
	const auto bConnectedSubsystemToFunctionCall = K2Schema->TryCreateConnection(SubsystemReturnPin, RequestFunctionSelfPin);
	check(bConnectedSubsystemToFunctionCall)
}


void BeamK2::ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& WrappedPinNames,
                                           const CheckParamIsValidForNodePredicate Predicate)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	WrappedPinNames.Reset();
	// Create the inputs and outputs		
	for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		const FProperty* Param = *PropIt;

		// Don't create a new pin if one exists already or if it's a pin for one of the handlers, we skip them.
		// The entire point of this node is to allow for "fake" sequential execution in blueprint (for better organizational purposes).
		if (!Param || Predicate(CustomNode, Param))
			continue;

		// We filter out all output pins because we create them by hand after we get all the input ones.
		constexpr EEdGraphPinDirection Direction = EGPD_Input;

		// Create, store and configure the pin to be the correct type.
		UEdGraphPin* Pin = CustomNode->CreatePin(Direction, NAME_None, Param->GetFName());

		// Make sure it's a hide-able pin here, if it is a hide-able pin in the given function
		Pin->bAdvancedView = Function->GetMetaData("AdvancedDisplay").Contains(Param->GetFName().ToString());

		// Set up the pin type based on the parameter's property type.
		const bool _ = K2Schema->ConvertPropertyToPinType(Param, /*out*/ Pin->PinType);
		K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);

		// Generate the pin's tooltip from the function docs.
		UK2Node_CallFunction::GeneratePinTooltipFromFunction(*Pin, Function);

		// Keep track of the pins that come from the Request Function		
		WrappedPinNames.Add(Pin->GetName());
	}
}

void BeamK2::ParseFunctionForNodePins(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& InputWrappedPinNames, TArray<FString>& OutputWrappedPinNames, const CheckParamIsValidForNodePredicate Predicate)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	InputWrappedPinNames.Reset();
	OutputWrappedPinNames.Reset();
	// Create the inputs and outputs		
	for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		const FProperty* Param = *PropIt;

		// Don't create a new pin if one exists already or if it's a pin for one of the handlers, we skip them.
		// The entire point of this node is to allow for "fake" sequential execution in blueprint (for better organizational purposes).
		if (!Param || Predicate(CustomNode, Param))
			continue;

		// We ignore all Output parameters because we create these by hand.
		const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

		// We filter out all output pins because we create them by hand after we get all the input ones.
		EEdGraphPinDirection Direction = bIsOutputParam ? EGPD_Output : EGPD_Input;

		// Create, store and configure the pin to be the correct type.
		UEdGraphPin* Pin = CustomNode->CreatePin(Direction, NAME_None, Param->GetFName());

		// Make sure it's a hide-able pin here, if it is a hide-able pin in the given function
		Pin->bAdvancedView = Function->GetMetaData("AdvancedDisplay").Contains(Param->GetFName().ToString());

		// Set up the pin type based on the parameter's property type.
		const bool _ = K2Schema->ConvertPropertyToPinType(Param, /*out*/ Pin->PinType);
		K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);

		// Generate the pin's tooltip from the function docs.
		UK2Node_CallFunction::GeneratePinTooltipFromFunction(*Pin, Function);

		// Keep track of the pins that come from the Request Function
		if (bIsOutputParam)
		{
			OutputWrappedPinNames.Add(Pin->GetName());
		}
		else
		{
			InputWrappedPinNames.Add(Pin->GetName());
		}
	}
}

void BeamK2::ParseFunctionForNodeOutputPinsArrayElement(UEdGraphNode* CustomNode, const UFunction* Function, TArray<FString>& OutputWrappedPinNames)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	OutputWrappedPinNames.Reset();
	// Create the outputs for the array elements	
	for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		const FProperty* Param = *PropIt;

		if (!Param)
			continue;

		// We ignore all Output parameters because we create these by hand.
		const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

		// if it's not a output or a array we should ignore
		if (!bIsOutputParam || !Param->IsA(FArrayProperty::StaticClass()))
		{
			continue;
		}

		// We filter out all output pins because we create them by hand after we get all the input ones.
		EEdGraphPinDirection Direction = EGPD_Output;

		FArrayProperty* InnerArrayProperty = CastField<FArrayProperty>(*PropIt);
		Param = InnerArrayProperty->Inner;
		FString PinFriendlyName = Param->GetName() + " - Element";


		// Create, store and configure the pin to be the correct type.
		UEdGraphPin* Pin = CustomNode->CreatePin(Direction, NAME_None, *(Param->GetName() + "Element"));
		Pin->PinFriendlyName = FText::FromString(PinFriendlyName);

		// Make sure it's a hide-able pin here, if it is a hide-able pin in the given function
		Pin->bAdvancedView = Function->GetMetaData("AdvancedDisplay").Contains(Param->GetFName().ToString());

		// Set up the pin type based on the parameter's property type.
		const bool _ = K2Schema->ConvertPropertyToPinType(Param, /*out*/ Pin->PinType);
		K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);

		// Generate the pin's tooltip from the function docs.
		UK2Node_CallFunction::GeneratePinTooltipFromFunction(*Pin, Function);

		OutputWrappedPinNames.Add(Param->GetName());
	}
}

void BeamK2::ParseFunctionForNodeInputPins(UEdGraphNode* CustomNode, const UFunction* Function, const TArray<FName> PinsToAdd, bool bFailIfNotFound)
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the inputs and outputs
	for (const auto ToAdd : PinsToAdd)
	{
		const FProperty* Param = Function->FindPropertyByName(ToAdd);
		if (!Param)
		{
			if (bFailIfNotFound)
				check(false)
			else
				continue;
		}

		// We filter out all output pins because we create them by hand after we get all the input ones.
		constexpr EEdGraphPinDirection Direction = EGPD_Input;

		// Create, store and configure the pin to be the correct type.
		UEdGraphPin* Pin = CustomNode->CreatePin(Direction, NAME_None, Param->GetFName());

		// Make sure it's a hide-able pin here, if it is a hide-able pin in the given function
		Pin->bAdvancedView = Function->GetMetaData("AdvancedDisplay").Contains(Param->GetFName().ToString());

		// Set up the pin type based on the parameter's property type.
		const bool _ = K2Schema->ConvertPropertyToPinType(Param, /*out*/ Pin->PinType);
		K2Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);

		// Generate the pin's tooltip from the function docs.
		UK2Node_CallFunction::GeneratePinTooltipFromFunction(*Pin, Function);
	}
}

#undef LOCTEXT_NAMESPACE
