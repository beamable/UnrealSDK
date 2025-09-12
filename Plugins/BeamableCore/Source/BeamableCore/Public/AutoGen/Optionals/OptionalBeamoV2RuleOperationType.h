#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2RuleOperationType.h"

#include "OptionalBeamoV2RuleOperationType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalBeamoV2RuleOperationTypeLibrary.MakeOptional", BeamOptionalType="EBeamBeamoV2RuleOperationType"))
struct BEAMABLECORE_API FOptionalBeamoV2RuleOperationType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EBeamBeamoV2RuleOperationType Val;

	FOptionalBeamoV2RuleOperationType();

	explicit FOptionalBeamoV2RuleOperationType(EBeamBeamoV2RuleOperationType Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};