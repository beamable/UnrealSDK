#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/TournamentEntry.h"

#include "OptionalTournamentEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalTournamentEntryLibrary.MakeOptional", BeamOptionalType="UTournamentEntry*"))
struct BEAMABLECORE_API FOptionalTournamentEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTournamentEntry* Val;

	FOptionalTournamentEntry();

	explicit FOptionalTournamentEntry(UTournamentEntry* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};