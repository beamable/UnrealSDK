#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/StringStringKeyValuePair.h"

#include "OptionalArrayOfStringStringKeyValuePair.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfStringStringKeyValuePairLibrary.MakeOptional", BeamOptionalType="TArray<UStringStringKeyValuePair*>"))
struct BEAMABLECORE_API FOptionalArrayOfStringStringKeyValuePair : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UStringStringKeyValuePair*> Val;

	FOptionalArrayOfStringStringKeyValuePair();

	explicit FOptionalArrayOfStringStringKeyValuePair(TArray<UStringStringKeyValuePair*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};