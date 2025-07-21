#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2FederationType.h"

#include "OptionalBeamoV2FederationType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2FederationTypeLibrary.MakeOptional", BeamOptionalType="EBeamBeamoV2FederationType"))
struct BEAMABLECORE_API FOptionalBeamoV2FederationType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamBeamoV2FederationType Val;

	FOptionalBeamoV2FederationType();

	explicit FOptionalBeamoV2FederationType(EBeamBeamoV2FederationType Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};