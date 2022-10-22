#pragma once

#include "CoreMinimal.h"
#include "K2Node_AddPinInterface.h"
#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"

#include "K2BeamNode_WaitAll.generated.h"

#define LOCTEXT_NAMESPACE "K2Node_WaitAll"

UCLASS(meta=(BeamFlow))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_WaitAll : public UK2Node, public IK2Node_AddPinInterface
{
	GENERATED_BODY()
public:
	static const FName SelfFunctionName;
	static const FName WaitAllFunctionName;
	static const FName P_CompleteCallback;
	static const FName P_Contexts;
	static const FName P_Requests;

	UPROPERTY()
	TArray<FString> WrappedWaitAllFunctionPinNames;

	UPROPERTY()
	bool bIsInBeamFlowMode = true;

	UPROPERTY()
	int32 NumPins = 0;

	static const FName P_Responses;
	static const FName P_Errors;
	virtual bool IsNodeSafeToIgnore() const override;
	virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;


	virtual FText GetMenuCategory() const override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	FSlateIcon GetIconAndTint(FLinearColor& OutColor) const;
	FLinearColor GetNodeTitleColor() const;
	FName GetCornerIcon() const;

	virtual void AllocateDefaultPins() override;
	UEdGraphPin* CreateContextInputPin(int32 PinIdx);

	virtual void AddInputPin() override;
	virtual void RemoveInputPin(UEdGraphPin* Pin) override;
	virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;
	
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	void ExitBeamFlowMode();
	void CreateBeamFlowModePins();
	void EnterBeamFlowMode();

private:
};

#undef LOCTEXT_NAMESPACE
