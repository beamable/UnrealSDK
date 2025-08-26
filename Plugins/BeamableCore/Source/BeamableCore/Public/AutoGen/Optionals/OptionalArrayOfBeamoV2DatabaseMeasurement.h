#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurement.h"

#include "OptionalArrayOfBeamoV2DatabaseMeasurement.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2DatabaseMeasurementLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2DatabaseMeasurement*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2DatabaseMeasurement : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2DatabaseMeasurement*> Val;

	FOptionalArrayOfBeamoV2DatabaseMeasurement();

	explicit FOptionalArrayOfBeamoV2DatabaseMeasurement(TArray<UBeamoV2DatabaseMeasurement*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};