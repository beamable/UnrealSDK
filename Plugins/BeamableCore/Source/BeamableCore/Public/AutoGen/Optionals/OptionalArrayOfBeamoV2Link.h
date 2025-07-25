#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Link.h"

#include "OptionalArrayOfBeamoV2Link.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2LinkLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2Link*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2Link : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2Link*> Val;

	FOptionalArrayOfBeamoV2Link();

	explicit FOptionalArrayOfBeamoV2Link(TArray<UBeamoV2Link*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};