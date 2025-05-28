#pragma once

#include "BeamBackend/BeamBackend.h"
class UBeamBackendTestCallbacks;

BEGIN_DEFINE_SPEC(FBeamBackendSpec, "BeamableUnreal.BeamBackend",
                  EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
	UBeamBackend* BeamBackendSystem;
	UObject* RequestFuncUObject;
	FName RequestFuncName;

	UBeamBackendTestCallbacks* Callbacks;

	TArray<FDelegateHandle> RegisteredDelegatesDuringConnectivityTests;
END_DEFINE_SPEC(FBeamBackendSpec)
