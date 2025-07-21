#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SupportedFederation.h"

#include "OptionalBeamoV2SupportedFederation.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2SupportedFederationLibrary.MakeOptional", BeamOptionalType="UBeamoV2SupportedFederation*"))
struct BEAMABLECORE_API FOptionalBeamoV2SupportedFederation : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBeamoV2SupportedFederation* Val;

	FOptionalBeamoV2SupportedFederation();

	explicit FOptionalBeamoV2SupportedFederation(UBeamoV2SupportedFederation* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};