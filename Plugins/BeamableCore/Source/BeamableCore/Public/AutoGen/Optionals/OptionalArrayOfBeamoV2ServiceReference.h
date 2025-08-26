#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceReference.h"

#include "OptionalArrayOfBeamoV2ServiceReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceReference*> Val;

	FOptionalArrayOfBeamoV2ServiceReference();

	explicit FOptionalArrayOfBeamoV2ServiceReference(TArray<UBeamoV2ServiceReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};