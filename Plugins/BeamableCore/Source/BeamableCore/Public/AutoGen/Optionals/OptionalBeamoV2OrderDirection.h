#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2OrderDirection.h"

#include "OptionalBeamoV2OrderDirection.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2OrderDirectionLibrary.MakeOptional", BeamOptionalType="EBeamBeamoV2OrderDirection"))
struct BEAMABLECORE_API FOptionalBeamoV2OrderDirection : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamBeamoV2OrderDirection Val;

	FOptionalBeamoV2OrderDirection();

	explicit FOptionalBeamoV2OrderDirection(EBeamBeamoV2OrderDirection Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};