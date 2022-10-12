
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ItemCreateRequestBody.h"
#include "AutoGen/CurrencyChange.h"

#include "TrackPurchaseRequestBody.generated.h"

UCLASS(BlueprintType)
class UTrackPurchaseRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price In Local Currency")
	double PriceInLocalCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku Name")
	FString SkuName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku Product Id")
	FString SkuProductId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Store")
	FString Store;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items")
	TArray<UItemCreateRequestBody*> ObtainItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency")
	TArray<UCurrencyChange*> ObtainCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchase Id")
	FString PurchaseId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Iso Currency Symbol")
	FString IsoCurrencySymbol;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};