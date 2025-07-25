#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StringStringKeyValuePair.h"

#include "OptionalArrayOfBeamoV2StringStringKeyValuePair.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2StringStringKeyValuePairLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2StringStringKeyValuePair*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2StringStringKeyValuePair : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2StringStringKeyValuePair*> Val;

	FOptionalArrayOfBeamoV2StringStringKeyValuePair();

	explicit FOptionalArrayOfBeamoV2StringStringKeyValuePair(TArray<UBeamoV2StringStringKeyValuePair*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};