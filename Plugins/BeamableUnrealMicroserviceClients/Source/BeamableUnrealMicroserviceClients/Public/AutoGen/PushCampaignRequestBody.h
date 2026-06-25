#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushOffer.h"

#include "PushCampaignRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPushCampaignRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FString Title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Deep Link", Category="Beam")
	FString DeepLink = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Campaign Id", Category="Beam")
	FString CampaignId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Node Id", Category="Beam")
	FString NodeId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	FString GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account Id", Category="Beam")
	FString AccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid Pid", Category="Beam")
	FString CidPid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Campaign Data", Category="Beam")
	FString CampaignData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offers", Category="Beam")
	TArray<UPushOffer*> Offers = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};