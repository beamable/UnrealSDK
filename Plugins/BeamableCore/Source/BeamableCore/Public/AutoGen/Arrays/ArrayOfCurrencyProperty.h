#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamArray.h"
#include "BeamableCore/Public/AutoGen/CurrencyProperty.h"

#include "ArrayOfCurrencyProperty.generated.h"
		
USTRUCT(BlueprintType, Category="Beam|₢ServiceName₢|Wrappers|Arrays")
struct BEAMABLECORE_API FArrayOfCurrencyProperty : public FBeamArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TArray<UCurrencyProperty*> Values;

	FArrayOfCurrencyProperty();

	explicit FArrayOfCurrencyProperty(const TArray<UCurrencyProperty*>& Values);

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;

	virtual void BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements) override;
};
