#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/CurrencyChange.h"

#include "TrackPurchaseRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTrackPurchaseRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price In Local Currency", Category="Beam")
	double PriceInLocalCurrency = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku Name", Category="Beam")
	FString SkuName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku Product Id", Category="Beam")
	FString SkuProductId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Store", Category="Beam")
	FString Store = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchase Id", Category="Beam")
	FString PurchaseId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Iso Currency Symbol", Category="Beam")
	FString IsoCurrencySymbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items", Category="Beam")
	TArray<UItemCreateRequestBody*> ObtainItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency", Category="Beam")
	TArray<UCurrencyChange*> ObtainCurrency = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};