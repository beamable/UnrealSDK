#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TournamentGroupEntry.h"

#include "OptionalTournamentGroupEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalTournamentGroupEntryLibrary.MakeOptional", BeamOptionalType="UTournamentGroupEntry*"))
struct BEAMABLECORE_API FOptionalTournamentGroupEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTournamentGroupEntry* Val;

	FOptionalTournamentGroupEntry();

	explicit FOptionalTournamentGroupEntry(UTournamentGroupEntry* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};