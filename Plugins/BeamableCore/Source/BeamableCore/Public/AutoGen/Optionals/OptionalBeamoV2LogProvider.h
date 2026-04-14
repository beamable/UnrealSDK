#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2LogProvider.h"

#include "OptionalBeamoV2LogProvider.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2LogProviderLibrary.MakeOptional", BeamOptionalType="EBeamBeamoV2LogProvider"))
struct BEAMABLECORE_API FOptionalBeamoV2LogProvider : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamBeamoV2LogProvider Val;

	FOptionalBeamoV2LogProvider();

	explicit FOptionalBeamoV2LogProvider(EBeamBeamoV2LogProvider Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};