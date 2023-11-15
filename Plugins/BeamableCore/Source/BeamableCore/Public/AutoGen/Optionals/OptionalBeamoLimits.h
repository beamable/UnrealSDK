#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoLimits.h"

#include "OptionalBeamoLimits.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoLimitsLibrary.MakeOptional", BeamOptionalType="UBeamoLimits*"))
struct BEAMABLECORE_API FOptionalBeamoLimits : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBeamoLimits* Val;

	FOptionalBeamoLimits();

	explicit FOptionalBeamoLimits(UBeamoLimits* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};