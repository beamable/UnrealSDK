
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Price.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ItemCreateRequestBody.h"
#include "AutoGen/CurrencyChange.h"

#include "PlayerOfferView.generated.h"

UCLASS(BlueprintType)
class UPlayerOfferView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Coupons")
	int32 Coupons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price")
	UPrice* Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Button Text")
	FOptionalString ButtonText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Titles")
	TArray<FString> Titles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items")
	TArray<UItemCreateRequestBody*> ObtainItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency")
	TArray<UCurrencyChange*> ObtainCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Images")
	TArray<FString> Images;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Descriptions")
	TArray<FString> Descriptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain")
	TArray<FString> Obtain;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};