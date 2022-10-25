
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/EventRewardContent.h"

#include "OptionalArrayOfEventRewardContent.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfEventRewardContentLibrary.MakeOptional"))
struct BEAMABLECORE_API FOptionalArrayOfEventRewardContent : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UEventRewardContent*> Val;

	FOptionalArrayOfEventRewardContent();

	explicit FOptionalArrayOfEventRewardContent(TArray<UEventRewardContent*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};