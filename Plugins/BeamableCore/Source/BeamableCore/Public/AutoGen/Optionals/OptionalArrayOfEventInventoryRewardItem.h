#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventInventoryRewardItem.h"

#include "OptionalArrayOfEventInventoryRewardItem.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventInventoryRewardItemLibrary.MakeOptional", BeamOptionalType="TArray<UEventInventoryRewardItem*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventInventoryRewardItem : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventInventoryRewardItem*> Val;

	FOptionalArrayOfEventInventoryRewardItem();

	explicit FOptionalArrayOfEventInventoryRewardItem(TArray<UEventInventoryRewardItem*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};