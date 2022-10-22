// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecuteRequestNodes/AutoGen/K2BeamNode_ExecuteRequest_BasicAccountsGetMe.h"

#include "BeamK2.h"
#include "ExecuteRequestNodes/BeamK2ExecuteRequest.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "ToolMenu.h"
#include "Kismet2/BlueprintEditorUtils.h"

#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ExecuteRequest_BasicAccountsGetMe"

using namespace BeamK2;
using namespace ExecuteRequest;

const FName UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::SelfFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
const FName UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::RequestFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetMe);
const FName UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::MakeFunctionName = GET_FUNCTION_NAME_CHECKED(UBasicAccountsGetMeRequest, MakeBasicAccountsGetMeRequest);

bool UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::IsNodeSafeToIgnore() const
{
	return true;
}


bool UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::IsCompatibleWithGraph(const UEdGraph* Graph) const
{
	return IsMacroOrEventGraph(Graph) && Super::IsCompatibleWithGraph(Graph);
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetMenuCategory() const
{
	return LOCTEXT("BeamNodeCategory", "Beam|API Execute Nodes|Account");
}

FText UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("BeamNodeTitle", "Beam Request - Account - Get Me");
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto _ = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	const auto RequestFunction = FindFunctionByName<UBeamAccountsApi>(RequestFunctionName);

	// Create the input pins for this ExecuteRequest node
	// Start by grabbing the request function, which give us the output pins of the graph this node hides as well as a couple of the input ones.
	ParseFunctionForNodeInputPins(this, RequestFunction, WrappedRequestFunctionPinNames, IsIgnoredInputPinForExecuteRequestNode);	
	UE_LOG(LogTemp, Display, TEXT("Found Pin %d, while parsing request function %s"), WrappedRequestFunctionPinNames.Num())
	// Then, grab the Make___Request function. This give us the the data input pins of the graph this node hides.
	ParseFunctionForNodeInputPins(this, FindFunctionByName<UBasicAccountsGetMeRequest>(MakeFunctionName), WrappedMakeFunctionPinNames, IsIgnoredInputPinForExecuteRequestNode);
	UE_LOG(LogTemp, Display, TEXT("Found Pin %d, while parsing make function %s"), WrappedMakeFunctionPinNames.Num())
	// Create the output pins in an order that improves usability.
	CreateExecuteRequestPins(this, UBasicAccountsGetMeRequest::StaticClass());
	if (bIsInBeamFlowMode)
		CreateBeamFlowModePins(this, UAccountPlayerView::StaticClass());
	else
		ParseFunctionForNodeInputPins(this, RequestFunction, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete}, true);
}

FSlateIcon UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetIconAndTint(FLinearColor& OutColor) const
{
	const auto Icon = Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIcon");
}

FLinearColor UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

FName UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetCornerIcon() const
{
	return FName("BeamIconSpaceship");
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	ExpandNodeImpl(this, bIsInBeamFlowMode, CompilerContext, SourceGraph,
	               UBeamAccountsApi::StaticClass(),
	               UBasicAccountsGetMeRequest::StaticClass(),
	               SelfFunctionName, RequestFunctionName, MakeFunctionName,
	               L"OnBasicAccountsGetMeSuccess",
	               L"OnBasicAccountsGetMeError",
	               L"OnBasicAccountsGetMeComplete",
	               WrappedRequestFunctionPinNames, WrappedMakeFunctionPinNames);
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);
	if (!Context->bIsDebugging)
	{
		static auto ExecuteRequestNodeName = FName("ExecuteRequestNodeName");
		const auto ExecuteRequestNodeNameStr = LOCTEXT("ExecuteRequestNodeName", "Execute Request Node");

		FToolMenuSection& Section = Menu->AddSection(ExecuteRequestNodeName, ExecuteRequestNodeNameStr);

		const FName MenuEntryName = !bIsInBeamFlowMode ? "EnterBeamFlowMode" : "ExitBeamFlowMode";
		const FText MenuEntryLabel = !bIsInBeamFlowMode ? LOCTEXT("EnterBeamFlowMode", "Enter Beam Flow Mode") : LOCTEXT("ExitBeamFlowMode", "Exit Beam Flow Mode");
		const FText MenuEntryTooltip = LOCTEXT("RemovePinTooltip", "Toggles Beam Flow Mode. Basically, decides whether you want a sequential flow or the ability to use create event.");

		const FUIAction MenuAction = !bIsInBeamFlowMode
			                             ? FUIAction(
				                             FExecuteAction::CreateUObject(const_cast<UK2BeamNode_ExecuteRequest_BasicAccountsGetMe*>(this),
				                                                           &UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::EnterBeamFlowMode)
			                             )
			                             : FUIAction(
				                             FExecuteAction::CreateUObject(const_cast<UK2BeamNode_ExecuteRequest_BasicAccountsGetMe*>(this),
				                                                           &UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::ExitBeamFlowMode)
			                             );

		Section.AddMenuEntry(MenuEntryName, MenuEntryLabel, MenuEntryTooltip, FSlateIcon(), MenuAction);
	}
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::ExitBeamFlowMode()
{
	FScopedTransaction Transaction(LOCTEXT("EnterEventModeTx", "EnterEventMode"));
	Modify();

	const auto RequestFunction = FindFunctionByName<UBeamAccountsApi>(RequestFunctionName);
	RemoveAllPins(this, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete, OP_ExecuteRequest_Response, OP_ExecuteRequest_Error});
	ParseFunctionForNodeInputPins(this, RequestFunction, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete}, true);

	bIsInBeamFlowMode = false;
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UK2BeamNode_ExecuteRequest_BasicAccountsGetMe::EnterBeamFlowMode()
{
	FScopedTransaction Transaction(LOCTEXT("ExitEventModeTx", "ExitEventMode"));
	Modify();

	RemoveAllPins(this, {OP_ExecuteRequest_OnSuccess, OP_ExecuteRequest_OnError, OP_ExecuteRequest_OnComplete});
	CreateBeamFlowModePins(this, UAccountPlayerView::StaticClass());

	bIsInBeamFlowMode = true;
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}


#undef LOCTEXT_NAMESPACE
