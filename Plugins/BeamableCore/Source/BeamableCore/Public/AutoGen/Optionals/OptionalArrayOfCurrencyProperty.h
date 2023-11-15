#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CurrencyProperty.h"

#include "OptionalArrayOfCurrencyProperty.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCurrencyPropertyLibrary.MakeOptional", BeamOptionalType="TArray<UCurrencyProperty*>"))
struct BEAMABLECORE_API FOptionalArrayOfCurrencyProperty : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCurrencyProperty*> Val;

	FOptionalArrayOfCurrencyProperty();

	explicit FOptionalArrayOfCurrencyProperty(TArray<UCurrencyProperty*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};