
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

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerReward : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Item Requests", Category="Beam")
	TArray<UItemCreateRequestBody*> AddItemRequests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Currency Map", Category="Beam")
	TMap<FString, FString> AddCurrencyMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Apply Vip Bonus", Category="Beam")
	FOptionalBool bApplyVipBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Change Currencies", Category="Beam")
	FOptionalArrayOfCurrencyChangeReward ChangeCurrencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Call Webhooks", Category="Beam")
	FOptionalArrayOfWebhookReward CallWebhooks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Add Items", Category="Beam")
	FOptionalArrayOfNewItemReward AddItems;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};