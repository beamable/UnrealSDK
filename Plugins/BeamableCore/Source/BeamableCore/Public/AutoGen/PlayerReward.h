
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyChangeReward.h"
#include "AutoGen/Optionals/OptionalArrayOfWebhookReward.h"
#include "AutoGen/Optionals/OptionalArrayOfNewItemReward.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "PlayerReward.generated.h"

UCLASS(BlueprintType)
class UPlayerReward : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FOptionalString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Item Requests")
	TArray<UItemCreateRequestBody*> AddItemRequests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Change Currencies")
	FOptionalArrayOfCurrencyChangeReward ChangeCurrencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Call Webhooks")
	FOptionalArrayOfWebhookReward CallWebhooks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Items")
	FOptionalArrayOfNewItemReward AddItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus")
	FOptionalBool bApplyVipBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Currency Map")
	TMap<FString, FString> AddCurrencyMap;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};