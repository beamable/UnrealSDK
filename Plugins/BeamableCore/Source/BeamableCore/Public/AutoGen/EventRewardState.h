#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/EventInventoryPendingRewards.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventInventoryRewardItem.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDouble.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRewardObtain.h"

#include "EventRewardState.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEventRewardState : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Claimed", Category="Beam")
	bool bClaimed = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Earned", Category="Beam")
	bool bEarned = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Inventory Rewards", Category="Beam")
	UEventInventoryPendingRewards* PendingInventoryRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min", Category="Beam")
	double Min = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max", Category="Beam")
	FOptionalDouble Max = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currencies", Category="Beam")
	FOptionalArrayOfEventInventoryRewardCurrency Currencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Item Rewards", Category="Beam")
	FOptionalArrayOfItemCreateRequestBody PendingItemRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Items", Category="Beam")
	FOptionalArrayOfEventInventoryRewardItem Items = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain", Category="Beam")
	FOptionalArrayOfEventRewardObtain Obtain = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Currency Rewards", Category="Beam")
	FOptionalMapOfString PendingCurrencyRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Entitlement Rewards", Category="Beam")
	FOptionalMapOfString PendingEntitlementRewards = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};