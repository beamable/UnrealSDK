// Copyright Epic Games, Inc. All Rights Reserved.

#include "BEAMPROJ_BeamFarm.h"

#define LOCTEXT_NAMESPACE "FBEAMPROJ_BeamFarmModule"

void FBEAMPROJ_BeamFarmModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBEAMPROJ_BeamFarmModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBEAMPROJ_BeamFarmModule, BEAMPROJ_BeamFarm)