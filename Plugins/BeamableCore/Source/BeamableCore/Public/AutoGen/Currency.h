
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyProperty.h"

#include "Currency.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrency : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount", Category="Beam")
	int64 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Properties", Category="Beam")
	FOptionalArrayOfCurrencyProperty Properties;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};