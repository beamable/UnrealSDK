
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "SubscriberDetailsResponse.generated.h"

UCLASS(BlueprintType)
class USubscriberDetailsResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Channel Prefix")
	FString CustomChannelPrefix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player For Realm Channel")
	FString PlayerForRealmChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Authentication Key")
	FString AuthenticationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Global Notification Channel")
	FOptionalString GameGlobalNotificationChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Notification Channel")
	FString GameNotificationChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Subscribe Key")
	FString SubscribeKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Channel")
	FString PlayerChannel;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};