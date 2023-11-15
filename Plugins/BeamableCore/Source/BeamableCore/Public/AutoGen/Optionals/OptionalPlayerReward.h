#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/PlayerReward.h"

#include "OptionalPlayerReward.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalPlayerRewardLibrary.MakeOptional", BeamOptionalType="UPlayerReward*"))
struct BEAMABLECORE_API FOptionalPlayerReward : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPlayerReward* Val;

	FOptionalPlayerReward();

	explicit FOptionalPlayerReward(UPlayerReward* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};