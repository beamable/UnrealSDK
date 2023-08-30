#include "BeamableCoreEditorCommands.h"

#define LOCTEXT_NAMESPACE "FTutorialPluginEditorModule"

void FBeamableCoreEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenBeamableWindowCommand, "Beamable", "Opens the Beamable window!", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CreateContentObjectInLocalManifest, "Beamable - Create Local Content Object", "Edits the selected content object!", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(EditContentObjectInLocalManifest, "Beamable - Edit Local Content Object", "Edits the selected content object!", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(PublishManifest, "Beamable - Publish Content Manifest", "Pushes the current local manifest to your current realm!", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DownloadManifest, "Beamable - Download Content Manifest", "Pulls the current local manifest to your current realm!", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
