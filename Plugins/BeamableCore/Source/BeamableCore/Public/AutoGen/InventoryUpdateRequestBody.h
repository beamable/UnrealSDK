
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalMapOfInt64.h"
#include "AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"

#include "InventoryUpdateRequestBody.generated.h"

UCLASS(BlueprintType)
class UInventoryUpdateRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	FOptionalMapOfInt64 Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Empty")
	bool bEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency Properties")
	FOptionalMapOfArrayOfCurrencyProperty CurrencyProperties;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency Content Ids")
	TArray<FString> CurrencyContentIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus")
	FOptionalBool bApplyVipBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Item Content Ids")
	TArray<FString> ItemContentIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Update Items")
	FOptionalArrayOfItemUpdateRequestBody UpdateItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="New Items")
	FOptionalArrayOfItemCreateRequestBody NewItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction")
	FOptionalString Transaction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delete Items")
	FOptionalArrayOfItemDeleteRequestBody DeleteItems;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};