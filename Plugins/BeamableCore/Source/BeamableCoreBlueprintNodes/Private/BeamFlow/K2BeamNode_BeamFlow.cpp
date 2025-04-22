// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_BeamFlow.h"


#include "BlueprintNodeSpawner.h"
#include "ScopedTransaction.h"
#include "SourceCodeNavigation.h"
#include "ToolMenu.h"

#define LOCTEXT_NAMESPACE "BeamK2_BeamFlow"

void UK2BeamNode_BeamFlow::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto FlowPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_BeamFlow, bIsInBeamFlowMode);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(FlowPropName.ToString()))
	{
		if (bIsInBeamFlowMode)
			EnterBeamFlowMode();
		else
			ExitBeamFlowMode();
	}
}

bool UK2BeamNode_BeamFlow::IsNodeSafeToIgnore() const
{
	return true;
}


bool UK2BeamNode_BeamFlow::IsCompatibleWithGraph(const UEdGraph* Graph) const
{
	return BeamK2::IsMacroOrEventGraph(Graph) && Super::IsCompatibleWithGraph(Graph);
}

void UK2BeamNode_BeamFlow::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2BeamNode_BeamFlow::GetMenuCategory() const
{
	return FText::FromString(FString::Printf(TEXT("Beam|%s|Operation"), *GetServiceName()));
}

FString UK2BeamNode_BeamFlow::GetServiceName() const
{
	return FString("NullService");
}

FSlateIcon UK2BeamNode_BeamFlow::GetIconAndTint(FLinearColor& OutColor) const
{
	const auto Icon = Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_BeamFlow::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

FName UK2BeamNode_BeamFlow::GetCornerIcon() const
{
	return FName("BeamIcon_AutoGenRequests");
}

UObject* UK2BeamNode_BeamFlow::GetJumpTargetForDoubleClick() const
{
	return Super::GetJumpTargetForDoubleClick();
}

void UK2BeamNode_BeamFlow::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (Context->bIsDebugging) return;

	static auto NodeName = FName("BeamFlowNode");
	const auto NodeNameStr = LOCTEXT("BeamFlowNode", "Beam Flow");

	FToolMenuSection& Section = Menu->AddSection(NodeName, NodeNameStr);

	const FName MenuEntryName = !bIsInBeamFlowMode ? "EnterBeamFlowMode" : "ExitBeamFlowMode";
	const FText MenuEntryLabel = !bIsInBeamFlowMode ? LOCTEXT("EnterBeamFlowMode", "Enter Beam Flow Mode") : LOCTEXT("ExitBeamFlowMode", "Exit Beam Flow Mode");
	const FText MenuEntryTooltip = LOCTEXT("RemovePinTooltip", "Toggles Beam Flow mode on/off. Basically, decides whether you want a sequential flow or the ability to use create event.");

	const FUIAction MenuAction = !bIsInBeamFlowMode
		                             ? FUIAction(
			                             FExecuteAction::CreateUObject(const_cast<UK2BeamNode_BeamFlow*>(this),
			                                                           &UK2BeamNode_BeamFlow::EnterBeamFlowMode)
		                             )
		                             : FUIAction(
			                             FExecuteAction::CreateUObject(const_cast<UK2BeamNode_BeamFlow*>(this),
			                                                           &UK2BeamNode_BeamFlow::ExitBeamFlowMode)
		                             );

	Section.AddMenuEntry(MenuEntryName, MenuEntryLabel, MenuEntryTooltip, FSlateIcon(), MenuAction);
}

void UK2BeamNode_BeamFlow::ExitBeamFlowMode()
{
	FScopedTransaction Transaction(LOCTEXT("ExitBeamFlowModeTx", "ExitBeamFlowMode"));
	Modify();

	bIsInBeamFlowMode = false;
	ExitBeamFlowModeImpl();

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UK2BeamNode_BeamFlow::EnterBeamFlowMode()
{
	FScopedTransaction Transaction(LOCTEXT("EnterBeamFlowModeTx", "EnterBeamFlowMode"));
	Modify();

	bIsInBeamFlowMode = true;
	EnterBeamFlowModeImpl();

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UK2BeamNode_BeamFlow::ExitBeamFlowModeImpl()
{
}

void UK2BeamNode_BeamFlow::EnterBeamFlowModeImpl()
{
}


#undef LOCTEXT_NAMESPACE
