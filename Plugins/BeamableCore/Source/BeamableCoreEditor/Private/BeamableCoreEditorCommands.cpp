#include "BeamableCoreEditorCommands.h"

#define LOCTEXT_NAMESPACE "FTutorialPluginEditorModule"

void FBeamableCoreEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenBeamableWindowCommand, "Beamable", "Opens the Beamable window!", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE