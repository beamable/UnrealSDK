
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/EventInventoryRewardItem.h"

#include "OptionalArrayOfEventInventoryRewardItem.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfEventInventoryRewardItemLibrary.MakeOptionalArrayOfEventInventoryRewardItem"))
struct FOptionalArrayOfEventInventoryRewardItem : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UEventInventoryRewardItem*> Val;

	FOptionalArrayOfEventInventoryRewardItem();

	explicit FOptionalArrayOfEventInventoryRewardItem(TArray<UEventInventoryRewardItem*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};