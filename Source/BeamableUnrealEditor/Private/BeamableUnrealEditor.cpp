#include "BeamableUnrealEditor.h"

#include "BeamableCoreEditor.h"
#include "BeamableUtilityCommands.h"
#include "Editor.h"
#include "LevelEditor.h"
#include "BeamableUnrealEditor/BeamProjSyncSubsystem.h"

#define LOCTEXT_NAMESPACE "FBeamableUnrealEditorModule"

void FBeamableUnrealEditorModule::StartupModule()
{
	FBeamableUtilityCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FBeamableUtilityCommands::Get().SyncProj,
		FExecuteAction::CreateRaw(this, &FBeamableUnrealEditorModule::SyncAllOverridenDirectories)
	);

	auto& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	const TSharedPtr<FExtender> NewToolbarExtender = MakeShareable<FExtender>(new FExtender());
	NewToolbarExtender->AddToolBarExtension("ProjectSettings", EExtensionHook::Before,
	                                        PluginCommands, FToolBarExtensionDelegate::CreateStatic(&FBeamableUnrealEditorModule::AddBeamableButtons));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(NewToolbarExtender);
}

void FBeamableUnrealEditorModule::ShutdownModule()
{
	FBeamableUtilityCommands::Unregister();
}

void FBeamableUnrealEditorModule::AddBeamableButtons(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FBeamableUtilityCommands::Get().SyncProj, NAME_None,
	                         LOCTEXT("Beamable", "Beamable"), LOCTEXT("BeamableTooltip", "Sync Plugin Project"),
	                         FSlateIcon(FName(TEXT("BeamableCore")), FName(TEXT("BeamIcon_ResyncProj"))));
}

void FBeamableUnrealEditorModule::SyncAllOverridenDirectories()
{
	if (GetDefault<UBeamProjSyncSubsystem>()->SyncAllOverridenDirectories())
	{
		FMessageDialog::Open(EAppMsgCategory::Success, EAppMsgType::Type::Ok, FText::FromString("Success on sync project to sample."));
	}
	else
	{
		FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Type::Ok, FText::FromString("Error on sync project to sample."));
	}
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBeamableUnrealEditorModule, BeamableUnrealEditor)
