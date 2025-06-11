#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBeamableUnrealEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<class FUICommandList> PluginCommands;

	static void AddBeamableButtons(FToolBarBuilder& Builder);

	void SyncAllOverridenDirectories();
};
