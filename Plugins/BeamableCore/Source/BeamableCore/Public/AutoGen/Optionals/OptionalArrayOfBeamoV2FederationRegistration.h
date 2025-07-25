#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistration.h"

#include "OptionalArrayOfBeamoV2FederationRegistration.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2FederationRegistrationLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2FederationRegistration*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2FederationRegistration : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2FederationRegistration*> Val;

	FOptionalArrayOfBeamoV2FederationRegistration();

	explicit FOptionalArrayOfBeamoV2FederationRegistration(TArray<UBeamoV2FederationRegistration*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};