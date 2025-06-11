#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBeamCid.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"
#include "Content/BeamContentObject.h"

#include "Content/MockBeamContentObject.h"


BEGIN_DEFINE_SPEC(FBeamContentObjectSpec, "BeamableUnreal.ContentObject", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
	UMockBeamContentObject* ContentObject;
END_DEFINE_SPEC(FBeamContentObjectSpec)
