
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/EventInventoryRewardCurrency.h"

#include "OptionalArrayOfEventInventoryRewardCurrency.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfEventInventoryRewardCurrencyLibrary.MakeOptionalArrayOfEventInventoryRewardCurrency"))
struct FOptionalArrayOfEventInventoryRewardCurrency : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UEventInventoryRewardCurrency*> Val;

	FOptionalArrayOfEventInventoryRewardCurrency();

	explicit FOptionalArrayOfEventInventoryRewardCurrency(TArray<UEventInventoryRewardCurrency*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};