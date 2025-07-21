#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceDependencyReference.h"

#include "OptionalArrayOfBeamoV2ServiceDependencyReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceDependencyReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceDependencyReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceDependencyReference*> Val;

	FOptionalArrayOfBeamoV2ServiceDependencyReference();

	explicit FOptionalArrayOfBeamoV2ServiceDependencyReference(TArray<UBeamoV2ServiceDependencyReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};