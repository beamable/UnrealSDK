
#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USubscriberDetailsResponseLibrary::SubscriberDetailsResponseToJsonString(const USubscriberDetailsResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

USubscriberDetailsResponse* USubscriberDetailsResponseLibrary::Make(FString CustomChannelPrefix, FString PlayerForRealmChannel, FString AuthenticationKey, FString GameNotificationChannel, FString SubscribeKey, FString PlayerChannel, TArray<FString> PlayerChannels, FOptionalString GameGlobalNotificationChannel, UObject* Outer)
{
	auto Serializable = NewObject<USubscriberDetailsResponse>(Outer);
	Serializable->CustomChannelPrefix = CustomChannelPrefix;
	Serializable->PlayerForRealmChannel = PlayerForRealmChannel;
	Serializable->AuthenticationKey = AuthenticationKey;
	Serializable->GameNotificationChannel = GameNotificationChannel;
	Serializable->SubscribeKey = SubscribeKey;
	Serializable->PlayerChannel = PlayerChannel;
	Serializable->PlayerChannels = PlayerChannels;
	Serializable->GameGlobalNotificationChannel = GameGlobalNotificationChannel;
	
	return Serializable;
}

void USubscriberDetailsResponseLibrary::Break(const USubscriberDetailsResponse* Serializable, FString& CustomChannelPrefix, FString& PlayerForRealmChannel, FString& AuthenticationKey, FString& GameNotificationChannel, FString& SubscribeKey, FString& PlayerChannel, TArray<FString>& PlayerChannels, FOptionalString& GameGlobalNotificationChannel)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		CustomChannelPrefix = Serializable->CustomChannelPrefix;
		PlayerForRealmChannel = Serializable->PlayerForRealmChannel;
		AuthenticationKey = Serializable->AuthenticationKey;
		GameNotificationChannel = Serializable->GameNotificationChannel;
		SubscribeKey = Serializable->SubscribeKey;
		PlayerChannel = Serializable->PlayerChannel;
		PlayerChannels = Serializable->PlayerChannels;
		GameGlobalNotificationChannel = Serializable->GameGlobalNotificationChannel;
	}
		
}

