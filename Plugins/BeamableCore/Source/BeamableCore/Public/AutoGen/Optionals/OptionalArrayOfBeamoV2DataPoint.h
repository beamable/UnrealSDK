#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DataPoint.h"

#include "OptionalArrayOfBeamoV2DataPoint.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2DataPointLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2DataPoint*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2DataPoint : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2DataPoint*> Val;

	FOptionalArrayOfBeamoV2DataPoint();

	explicit FOptionalArrayOfBeamoV2DataPoint(TArray<UBeamoV2DataPoint*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};