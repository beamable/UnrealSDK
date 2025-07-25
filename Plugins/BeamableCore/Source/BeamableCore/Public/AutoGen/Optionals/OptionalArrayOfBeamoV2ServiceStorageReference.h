#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageReference.h"

#include "OptionalArrayOfBeamoV2ServiceStorageReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceStorageReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceStorageReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceStorageReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceStorageReference*> Val;

	FOptionalArrayOfBeamoV2ServiceStorageReference();

	explicit FOptionalArrayOfBeamoV2ServiceStorageReference(TArray<UBeamoV2ServiceStorageReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};