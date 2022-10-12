
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalMapOfInt64.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalMapOfInt64Library.MakeOptionalMapOfInt64"))
struct FOptionalMapOfInt64 : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, int64> Val;

	FOptionalMapOfInt64();

	explicit FOptionalMapOfInt64(TMap<FString, int64> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};