#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SupportedFederation.h"

#include "OptionalArrayOfBeamoV2SupportedFederation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2SupportedFederationLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2SupportedFederation*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2SupportedFederation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2SupportedFederation*> Val;

	FOptionalArrayOfBeamoV2SupportedFederation();

	explicit FOptionalArrayOfBeamoV2SupportedFederation(TArray<UBeamoV2SupportedFederation*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};