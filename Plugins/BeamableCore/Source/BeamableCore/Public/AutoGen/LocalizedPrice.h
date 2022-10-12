
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "LocalizedPrice.generated.h"

UCLASS(BlueprintType)
class ULocalizedPrice : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To")
	int64 To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price")
	int64 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price Localized")
	double PriceLocalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price Localized String")
	FString PriceLocalizedString;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};