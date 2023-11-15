#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventRewardObtain.h"

#include "OptionalArrayOfEventRewardObtain.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventRewardObtainLibrary.MakeOptional", BeamOptionalType="TArray<UEventRewardObtain*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventRewardObtain : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventRewardObtain*> Val;

	FOptionalArrayOfEventRewardObtain();

	explicit FOptionalArrayOfEventRewardObtain(TArray<UEventRewardObtain*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};