
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalArrayOfString.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfStringLibrary.MakeOptional"))
struct BEAMABLECORE_API FOptionalArrayOfString : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Val;

	FOptionalArrayOfString();

	explicit FOptionalArrayOfString(TArray<FString> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};