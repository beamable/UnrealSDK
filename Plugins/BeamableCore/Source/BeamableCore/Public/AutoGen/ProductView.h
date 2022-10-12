
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ProductView.generated.h"

UCLASS(BlueprintType)
class UProductView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localized Price")
	double LocalizedPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Iso Currency Code")
	FString IsoCurrencyCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Localized Price String")
	FString LocalizedPriceString;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};