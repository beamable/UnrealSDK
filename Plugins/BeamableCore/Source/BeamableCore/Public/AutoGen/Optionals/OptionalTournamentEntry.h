
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/TournamentEntry.h"

#include "OptionalTournamentEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalTournamentEntryLibrary.MakeOptionalTournamentEntry"))
struct FOptionalTournamentEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	UTournamentEntry* Val;

	FOptionalTournamentEntry();

	explicit FOptionalTournamentEntry(UTournamentEntry* Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};