
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/CurrencyChange.h"

#include "OptionalArrayOfCurrencyChange.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalArrayOfCurrencyChangeLibrary.MakeOptionalArrayOfCurrencyChange"))
struct FOptionalArrayOfCurrencyChange : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<UCurrencyChange*> Val;

	FOptionalArrayOfCurrencyChange();

	explicit FOptionalArrayOfCurrencyChange(TArray<UCurrencyChange*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};