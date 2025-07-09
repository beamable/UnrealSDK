#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoActorServiceReference.h"

#include "OptionalArrayOfBeamoActorServiceReference.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoActorServiceReferenceLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoActorServiceReference*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoActorServiceReference : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoActorServiceReference*> Val;

	FOptionalArrayOfBeamoActorServiceReference();

	explicit FOptionalArrayOfBeamoActorServiceReference(TArray<UBeamoActorServiceReference*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};