#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/EventRewardContent.h"

#include "OptionalArrayOfEventRewardContent.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfEventRewardContentLibrary.MakeOptional", BeamOptionalType="TArray<UEventRewardContent*>"))
struct BEAMABLECORE_API FOptionalArrayOfEventRewardContent : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UEventRewardContent*> Val;

	FOptionalArrayOfEventRewardContent();

	explicit FOptionalArrayOfEventRewardContent(TArray<UEventRewardContent*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};