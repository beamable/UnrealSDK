#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ObjectId.h"

#include "OptionalBeamoV2ObjectId.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2ObjectIdLibrary.MakeOptional", BeamOptionalType="UBeamoV2ObjectId*"))
struct BEAMABLECORE_API FOptionalBeamoV2ObjectId : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBeamoV2ObjectId* Val;

	FOptionalBeamoV2ObjectId();

	explicit FOptionalBeamoV2ObjectId(UBeamoV2ObjectId* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};