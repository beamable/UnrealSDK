#pragma once

#include "CoreMinimal.h"
#include "K2Node_AddPinInterface.h"
#include "KismetCompiler.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"

#include "K2BeamNode_WaitAll.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_WaitAll"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_WaitAll : public UK2BeamNode_BeamFlow, public IK2Node_AddPinInterface
{
	GENERATED_BODY()
public:
	static const FName SelfFunctionName;
	static const FName WaitAllFunctionName;
	static const FName P_CompleteCallback;
	static const FName P_RequestContexts;
	static const FName P_Operations;
	static const FName P_Waits;
	static const FName P_Evt;	

	UPROPERTY()
	TArray<FString> WrappedWaitAllFunctionPinNames;

	UPROPERTY()
	int32 NumPins = 0;

	virtual FText GetMenuCategory() const override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void AllocateDefaultPins() override;
	UEdGraphPin* CreateContextInputPin(int32 PinIdx);

	virtual void AddInputPin() override;
	virtual void RemoveInputPin(UEdGraphPin* Pin) override;
	virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostReconstructNode() override;

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	void PropagatePinType(UEdGraphPin* const& Pin) const;

	void CreateBeamFlowModePins();

	virtual void EnterBeamFlowModeImpl() override;
	virtual void ExitBeamFlowModeImpl() override;


private:
};

#undef LOCTEXT_NAMESPACE
