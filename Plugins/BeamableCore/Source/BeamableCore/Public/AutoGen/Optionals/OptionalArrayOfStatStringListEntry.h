
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/StatStringListEntry.h"

#include "OptionalArrayOfStatStringListEntry.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfStatStringListEntryLibrary.MakeOptionalArrayOfStatStringListEntry"))
struct FOptionalArrayOfStatStringListEntry : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UStatStringListEntry*> Val;

	FOptionalArrayOfStatStringListEntry();

	explicit FOptionalArrayOfStatStringListEntry(TArray<UStatStringListEntry*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};