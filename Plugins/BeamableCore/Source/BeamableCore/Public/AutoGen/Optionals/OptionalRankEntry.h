#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RankEntry.h"

#include "OptionalRankEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalRankEntryLibrary.MakeOptional", BeamOptionalType="URankEntry*"))
struct BEAMABLECORE_API FOptionalRankEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	URankEntry* Val;

	FOptionalRankEntry();

	explicit FOptionalRankEntry(URankEntry* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};