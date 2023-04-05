#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Content/BeamRuntimeContentCacheFactory.h"

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
};
