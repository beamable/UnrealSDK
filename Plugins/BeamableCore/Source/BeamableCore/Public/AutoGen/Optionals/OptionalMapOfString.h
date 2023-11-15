#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"


#include "OptionalMapOfString.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfStringLibrary.MakeOptional", BeamOptionalType="TMap<FString, FString>"))
struct BEAMABLECORE_API FOptionalMapOfString : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, FString> Val;

	FOptionalMapOfString();

	explicit FOptionalMapOfString(TMap<FString, FString> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};