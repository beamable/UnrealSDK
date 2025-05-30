#pragma once

#include "BeamBackend/BeamBackendTestCallbacks.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "Misc/AutomationTest.h"


class UBeamResponseCache;
class UBeamBackend;
BEGIN_DEFINE_SPEC(FBeamResponseCacheSpec, "BeamableUnreal.BeamResponseCache", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
	UBeamResponseCache* BeamResponseCache;
	UBeamBackend* BeamBackendSystem;
END_DEFINE_SPEC(FBeamResponseCacheSpec)
