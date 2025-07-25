#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#include "OptionalArrayOfBeamoV2Manifest.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ManifestLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2Manifest*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2Manifest : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2Manifest*> Val;

	FOptionalArrayOfBeamoV2Manifest();

	explicit FOptionalArrayOfBeamoV2Manifest(TArray<UBeamoV2Manifest*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};