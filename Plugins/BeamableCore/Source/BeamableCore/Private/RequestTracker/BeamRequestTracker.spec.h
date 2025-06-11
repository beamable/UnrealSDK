#pragma once

#include "BeamRequestTrackerTestCallbacks.h"
#include "RequestTracker/BeamRequestTracker.h"

BEGIN_DEFINE_SPEC(FBeamRequestTrackerSpec, "BeamableUnreal.RequestTracker", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
	UBeamBackend* BeamBackendSystem;
	UBeamRequestTracker* RequestTrackerSystem;

	UBeamRequestTrackerOperationTestCallbacks* OperationCallbacks;
	UBeamRequestTrackerWaitAllTestCallbacks* WaitAllCallbacks;

	TArray<FDelegateHandle> RegisteredDelegatesDuringConnectivityTests;
END_DEFINE_SPEC(FBeamRequestTrackerSpec)
