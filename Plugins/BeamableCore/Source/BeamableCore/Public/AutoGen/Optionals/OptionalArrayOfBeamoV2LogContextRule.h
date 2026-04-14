#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRule.h"

#include "OptionalArrayOfBeamoV2LogContextRule.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfBeamoV2LogContextRuleLibrary.MakeOptional", BeamOptionalType="TArray<UBeamoV2LogContextRule*>"))
struct BEAMABLECORE_API FOptionalArrayOfBeamoV2LogContextRule : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UBeamoV2LogContextRule*> Val;

	FOptionalArrayOfBeamoV2LogContextRule();

	explicit FOptionalArrayOfBeamoV2LogContextRule(TArray<UBeamoV2LogContextRule*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};