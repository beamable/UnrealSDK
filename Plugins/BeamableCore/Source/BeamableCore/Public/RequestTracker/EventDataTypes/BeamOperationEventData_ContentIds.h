#pragma once

#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "RequestTracker/BeamOperation.h"

#include "BeamOperationEventData_ContentIds.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamOperationEventData_ContentIds : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FBeamContentId> Ids;
};
