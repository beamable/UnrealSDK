
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "AutoGen/Arrays/ArrayOfCurrencyProperty.h"

#include "OptionalMapOfArrayOfCurrencyProperty.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="BeamableCore.OptionalMapOfArrayOfCurrencyPropertyLibrary.MakeOptional"))
struct BEAMABLECORE_API FOptionalMapOfArrayOfCurrencyProperty : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FArrayOfCurrencyProperty> Val;

	FOptionalMapOfArrayOfCurrencyProperty();

	explicit FOptionalMapOfArrayOfCurrencyProperty(TMap<FString, FArrayOfCurrencyProperty> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};