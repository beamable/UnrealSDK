#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CurrencyChangeReward.h"

#include "OptionalArrayOfCurrencyChangeReward.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCurrencyChangeRewardLibrary.MakeOptional", BeamOptionalType="TArray<UCurrencyChangeReward*>"))
struct BEAMABLECORE_API FOptionalArrayOfCurrencyChangeReward : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCurrencyChangeReward*> Val;

	FOptionalArrayOfCurrencyChangeReward();

	explicit FOptionalArrayOfCurrencyChangeReward(TArray<UCurrencyChangeReward*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};