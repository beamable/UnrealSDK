#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponse.h"

#include "SubscriberDetailsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USubscriberDetailsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Json", DisplayName="SubscriberDetailsResponse To JSON String")
	static FString SubscriberDetailsResponseToJsonString(const USubscriberDetailsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make SubscriberDetailsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="GameGlobalNotificationChannel, Outer", NativeMakeFunc))
	static USubscriberDetailsResponse* Make(FString CustomChannelPrefix, FString PlayerForRealmChannel, FString AuthenticationKey, FString GameNotificationChannel, FString SubscribeKey, FString PlayerChannel, TArray<FString> PlayerChannels, FOptionalString GameGlobalNotificationChannel, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Make/Break", DisplayName="Break SubscriberDetailsResponse", meta=(NativeBreakFunc))
	static void Break(const USubscriberDetailsResponse* Serializable, FString& CustomChannelPrefix, FString& PlayerForRealmChannel, FString& AuthenticationKey, FString& GameNotificationChannel, FString& SubscribeKey, FString& PlayerChannel, TArray<FString>& PlayerChannels, FOptionalString& GameGlobalNotificationChannel);
};