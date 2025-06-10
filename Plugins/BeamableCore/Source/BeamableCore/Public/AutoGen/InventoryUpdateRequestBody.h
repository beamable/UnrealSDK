#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"

#include "InventoryUpdateRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UInventoryUpdateRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus", Category="Beam")
	FOptionalBool bApplyVipBonus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction", Category="Beam")
	FOptionalString Transaction = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Update Items", Category="Beam")
	FOptionalArrayOfItemUpdateRequestBody UpdateItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="New Items", Category="Beam")
	FOptionalArrayOfItemCreateRequestBody NewItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delete Items", Category="Beam")
	FOptionalArrayOfItemDeleteRequestBody DeleteItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies", Category="Beam")
	FOptionalMapOfInt64 Currencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency Properties", Category="Beam")
	FOptionalMapOfArrayOfCurrencyProperty CurrencyProperties = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};