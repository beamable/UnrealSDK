#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/GamerTag.h"

#include "OptionalGamerTag.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalGamerTagLibrary.MakeOptional", BeamOptionalType="UGamerTag*"))
struct BEAMABLECORE_API FOptionalGamerTag : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UGamerTag* Val;

	FOptionalGamerTag();

	explicit FOptionalGamerTag(UGamerTag* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};