#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/MailRewards.h"

#include "OptionalMailRewards.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMailRewardsLibrary.MakeOptional", BeamOptionalType="UMailRewards*"))
struct BEAMABLECORE_API FOptionalMailRewards : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMailRewards* Val;

	FOptionalMailRewards();

	explicit FOptionalMailRewards(UMailRewards* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};