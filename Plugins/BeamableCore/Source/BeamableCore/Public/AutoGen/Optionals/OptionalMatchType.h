#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/MatchType.h"

#include "OptionalMatchType.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMatchTypeLibrary.MakeOptional", BeamOptionalType="UMatchType*"))
struct BEAMABLECORE_API FOptionalMatchType : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMatchType* Val;

	FOptionalMatchType();

	explicit FOptionalMatchType(UMatchType* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};