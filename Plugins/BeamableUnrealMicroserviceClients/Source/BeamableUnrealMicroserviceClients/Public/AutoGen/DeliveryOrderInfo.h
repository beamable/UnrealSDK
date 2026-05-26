#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryRequirement.h"

#include "DeliveryOrderInfo.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeliveryOrderInfo : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Order Id", Category="Beam")
	FString OrderId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Display Name", Category="Beam")
	FString DisplayName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Required Item Content Id", Category="Beam")
	FString RequiredItemContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reward Currency Id", Category="Beam")
	FString RewardCurrencyId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reward Amount", Category="Beam")
	int32 RewardAmount = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirements", Category="Beam")
	TArray<UDeliveryRequirement*> Requirements = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};