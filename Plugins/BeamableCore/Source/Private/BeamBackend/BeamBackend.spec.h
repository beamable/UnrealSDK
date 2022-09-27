#pragma once

#include "BeamBackend.h"
#include "RawAPIs/Auth/BeamAuthApi.h"
class UBeamBackendTestCallbacks;

BEGIN_DEFINE_SPEC(FBeamBackendSpec, "BeamableUnreal.BeamBackend", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	UBeamBackend* BeamBackendSystem;
	UBeamAuthApi* AuthApi;

	UBeamBackendTestCallbacks* Callbacks;

	FBeamConnectivity StatusAtTestRunStart;
	TArray<FDelegateHandle> RegisteredDelegatesDuringConnectivityTests;
END_DEFINE_SPEC(FBeamBackendSpec)
