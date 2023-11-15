#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/Arrays/ArrayOfCurrencyProperty.h"

#include "OptionalMapOfArrayOfCurrencyProperty.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalMapOfArrayOfCurrencyPropertyLibrary.MakeOptional", BeamOptionalType="TMap<FString, FArrayOfCurrencyProperty>"))
struct BEAMABLECORE_API FOptionalMapOfArrayOfCurrencyProperty : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FString, FArrayOfCurrencyProperty> Val;

	FOptionalMapOfArrayOfCurrencyProperty();

	explicit FOptionalMapOfArrayOfCurrencyProperty(TMap<FString, FArrayOfCurrencyProperty> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};