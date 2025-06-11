#pragma once

#include "UserSlots/BeamUserSlots.h"

class UBeamUserSlotsTestCallbacks;


BEGIN_DEFINE_SPEC(FBeamUserSlotsSpec, "BeamableUnreal.BeamUserSlots", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
	UBeamUserSlots* BeamUserSlots;
	TArray<FDelegateHandle> AddedTestHandlers;
	TArray<FName> AddedUObjectTestHandlers;

	UBeamUserSlotsTestCallbacks* Callbacks;
END_DEFINE_SPEC(FBeamUserSlotsSpec)
