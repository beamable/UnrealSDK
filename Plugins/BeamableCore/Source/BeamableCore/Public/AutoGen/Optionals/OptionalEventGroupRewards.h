#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventGroupRewards.h"

#include "OptionalEventGroupRewards.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalEventGroupRewardsLibrary.MakeOptional", BeamOptionalType="UEventGroupRewards*"))
struct BEAMABLECORE_API FOptionalEventGroupRewards : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UEventGroupRewards* Val;

	FOptionalEventGroupRewards();

	explicit FOptionalEventGroupRewards(UEventGroupRewards* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};