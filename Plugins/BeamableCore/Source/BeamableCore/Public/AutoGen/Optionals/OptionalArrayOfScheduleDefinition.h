#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/ScheduleDefinition.h"

#include "OptionalArrayOfScheduleDefinition.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfScheduleDefinitionLibrary.MakeOptional", BeamOptionalType="TArray<UScheduleDefinition*>"))
struct BEAMABLECORE_API FOptionalArrayOfScheduleDefinition : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UScheduleDefinition*> Val;

	FOptionalArrayOfScheduleDefinition();

	explicit FOptionalArrayOfScheduleDefinition(TArray<UScheduleDefinition*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};