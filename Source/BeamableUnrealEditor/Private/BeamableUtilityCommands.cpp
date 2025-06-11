// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamableUtilityCommands.h"

#define LOCTEXT_NAMESPACE "FUtilityCommandsPlugin"

void FBeamableUtilityCommands::RegisterCommands()
{
	UI_COMMAND(SyncProj, "Beamable", "Sync Plugin Proj", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
