#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "SubscriberDetailsResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USubscriberDetailsResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Channel Prefix", Category="Beam")
	FString CustomChannelPrefix = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player For Realm Channel", Category="Beam")
	FString PlayerForRealmChannel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Authentication Key", Category="Beam")
	FString AuthenticationKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Notification Channel", Category="Beam")
	FString GameNotificationChannel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subscribe Key", Category="Beam")
	FString SubscribeKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Channel", Category="Beam")
	FString PlayerChannel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Channels", Category="Beam")
	TArray<FString> PlayerChannels = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Global Notification Channel", Category="Beam")
	FOptionalString GameGlobalNotificationChannel = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};