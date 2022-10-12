
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventInventoryPendingRewards.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItem.h"
#include "AutoGen/Optionals/OptionalDouble.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRewardObtain.h"

#include "EventRewardState.generated.h"

UCLASS(BlueprintType)
class UEventRewardState : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Inventory Rewards")
	UEventInventoryPendingRewards* PendingInventoryRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies")
	FOptionalArrayOfEventInventoryRewardCurrency Currencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Currency Rewards")
	FOptionalMapOfString PendingCurrencyRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Item Rewards")
	FOptionalArrayOfItemCreateRequestBody PendingItemRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items")
	FOptionalArrayOfEventInventoryRewardItem Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min")
	double Min;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max")
	FOptionalDouble Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Earned")
	bool bEarned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Claimed")
	bool bClaimed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Entitlement Rewards")
	FOptionalMapOfString PendingEntitlementRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain")
	FOptionalArrayOfEventRewardObtain Obtain;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};