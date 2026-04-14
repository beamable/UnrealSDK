#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2PathRuleOperationType.h"

#include "OptionalBeamoV2PathRuleOperationType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2PathRuleOperationTypeLibrary.MakeOptional", BeamOptionalType="EBeamBeamoV2PathRuleOperationType"))
struct BEAMABLECORE_API FOptionalBeamoV2PathRuleOperationType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamBeamoV2PathRuleOperationType Val;

	FOptionalBeamoV2PathRuleOperationType();

	explicit FOptionalBeamoV2PathRuleOperationType(EBeamBeamoV2PathRuleOperationType Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};