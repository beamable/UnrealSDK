
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalMapOfString.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalMapOfStringLibrary.MakeOptionalMapOfString"))
struct FOptionalMapOfString : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> Val;

	FOptionalMapOfString();

	explicit FOptionalMapOfString(TMap<FString, FString> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};