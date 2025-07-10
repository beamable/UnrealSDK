#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoActorDataPoint.h"

#include "OptionalArrayOfBeamoActorDataPoint.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoActorDataPointLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoActorDataPoint*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoActorDataPoint : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoActorDataPoint*> Val;

	FOptionalArrayOfBeamoActorDataPoint();

	explicit FOptionalArrayOfBeamoActorDataPoint(TArray<UBeamoActorDataPoint*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};