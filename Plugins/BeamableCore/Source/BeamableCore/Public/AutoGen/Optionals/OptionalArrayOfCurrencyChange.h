#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamOptional.h"
#include "BeamableCore/Public/AutoGen/CurrencyChange.h"

#include "OptionalArrayOfCurrencyChange.generated.h"

// Has Native Make/Break require static blueprint pure functions to present as nodes that
// don't require an execution pin connection. This is super relevant for Blueprint UX. 
USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/BeamableCore.OptionalArrayOfCurrencyChangeLibrary.MakeOptional", BeamOptionalType="TArray<UCurrencyChange*>"))
struct BEAMABLECORE_API FOptionalArrayOfCurrencyChange : public FBeamOptional
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<UCurrencyChange*> Val;

	FOptionalArrayOfCurrencyChange();

	explicit FOptionalArrayOfCurrencyChange(TArray<UCurrencyChange*> Val);

	virtual const void* GetAddr() const override;

	virtual void Set(const void* Data) override;
};