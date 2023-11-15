#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/NewItemReward.h"

#include "OptionalArrayOfNewItemReward.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfNewItemRewardLibrary.MakeOptional", BeamOptionalType="TArray<UNewItemReward*>"))
struct BEAMABLECORE_API FOptionalArrayOfNewItemReward : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UNewItemReward*> Val;

	FOptionalArrayOfNewItemReward();

	explicit FOptionalArrayOfNewItemReward(TArray<UNewItemReward*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};