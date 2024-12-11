#pragma once

#include "CoreMinimal.h"
#include "AssetFactories/Content/BeamRuntimeContentCacheFactory.h"
#include "K2Node.h"
#include "Factories/Factory.h"

#include "BeamableCoreEditor.generated.h"

class BEAMABLECOREEDITOR_API FBeamableCoreEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	FDelegateHandle LocalContentManifestDataTableHandler;
	TSharedPtr<FBeamRuntimeContentCacheAssetTypeActions> BeamRuntimeContentCacheAssetTypeActions;

	static void AddBeamableButtons(FToolBarBuilder& Builder);
	void OpenMainBeamableWindow() const;

#if WITH_EDITOR

private:
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

public:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	static UEdGraphNode* CreateNewGraphNodeFromTemplate(UK2Node* NodeTemplate, UEdGraph* InGraph, const FVector2D& GraphLocation, UEdGraphPin* ConnectPin = nullptr);

	static UEdGraphNode* CreatePostBeginPlayEvent(UBlueprint* InBlueprint, UEdGraph* InGraph, FName InMemberName, const FVector2D& GraphLocation, TSubclassOf<class UObject> InMemberParentClass);

#endif
};


#if WITH_EDITOR

UCLASS()
class BEAMABLECOREEDITOR_API UBeamRuntimeSubsystemAction_Factory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

#endif
