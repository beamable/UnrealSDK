#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistration.h"

#include "OptionalArrayOfBeamoV2ServiceRegistration.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2ServiceRegistrationLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2ServiceRegistration*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2ServiceRegistration : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2ServiceRegistration*> Val;

	FOptionalArrayOfBeamoV2ServiceRegistration();

	explicit FOptionalArrayOfBeamoV2ServiceRegistration(TArray<UBeamoV2ServiceRegistration*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};