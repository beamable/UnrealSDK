#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/StatStringListEntry.h"

#include "OptionalArrayOfStatStringListEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfStatStringListEntryLibrary.MakeOptional", BeamOptionalType="TArray<UStatStringListEntry*>"))
struct BEAMABLECORE_API FOptionalArrayOfStatStringListEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UStatStringListEntry*> Val;

	FOptionalArrayOfStatStringListEntry();

	explicit FOptionalArrayOfStatStringListEntry(TArray<UStatStringListEntry*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};