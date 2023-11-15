#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/RankEntryStat.h"

#include "OptionalArrayOfRankEntryStat.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfRankEntryStatLibrary.MakeOptional", BeamOptionalType="TArray<URankEntryStat*>"))
struct BEAMABLECORE_API FOptionalArrayOfRankEntryStat : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<URankEntryStat*> Val;

	FOptionalArrayOfRankEntryStat();

	explicit FOptionalArrayOfRankEntryStat(TArray<URankEntryStat*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};