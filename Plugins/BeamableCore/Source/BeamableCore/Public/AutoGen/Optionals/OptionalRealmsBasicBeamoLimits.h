#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicBeamoLimits.h"

#include "OptionalRealmsBasicBeamoLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalRealmsBasicBeamoLimitsLibrary.MakeOptional", BeamOptionalType="URealmsBasicBeamoLimits*"))
struct BEAMABLECORE_API FOptionalRealmsBasicBeamoLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	URealmsBasicBeamoLimits* Val;

	FOptionalRealmsBasicBeamoLimits();

	explicit FOptionalRealmsBasicBeamoLimits(URealmsBasicBeamoLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};