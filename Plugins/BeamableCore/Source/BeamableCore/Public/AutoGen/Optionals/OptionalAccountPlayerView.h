#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "OptionalAccountPlayerView.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalAccountPlayerViewLibrary.MakeOptional", BeamOptionalType="UAccountPlayerView*"))
struct BEAMABLECORE_API FOptionalAccountPlayerView : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAccountPlayerView* Val;

	FOptionalAccountPlayerView();

	explicit FOptionalAccountPlayerView(UAccountPlayerView* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};