#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventInventoryRewardCurrency.h"

#include "OptionalArrayOfEventInventoryRewardCurrency.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventInventoryRewardCurrencyLibrary.MakeOptional", BeamOptionalType="TArray<UEventInventoryRewardCurrency*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventInventoryRewardCurrency : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventInventoryRewardCurrency*> Val;

	FOptionalArrayOfEventInventoryRewardCurrency();

	explicit FOptionalArrayOfEventInventoryRewardCurrency(TArray<UEventInventoryRewardCurrency*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};