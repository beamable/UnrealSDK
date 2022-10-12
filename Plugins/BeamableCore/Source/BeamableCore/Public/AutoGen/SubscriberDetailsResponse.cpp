
#include "AutoGen/SubscriberDetailsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void USubscriberDetailsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("customChannelPrefix"), CustomChannelPrefix);
	Serializer->WriteValue(TEXT("playerForRealmChannel"), PlayerForRealmChannel);
	Serializer->WriteValue(TEXT("authenticationKey"), AuthenticationKey);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);
	Serializer->WriteValue(TEXT("gameNotificationChannel"), GameNotificationChannel);
	Serializer->WriteValue(TEXT("subscribeKey"), SubscribeKey);
	Serializer->WriteValue(TEXT("playerChannel"), PlayerChannel);
}

void USubscriberDetailsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("customChannelPrefix"), CustomChannelPrefix);
	Serializer->WriteValue(TEXT("playerForRealmChannel"), PlayerForRealmChannel);
	Serializer->WriteValue(TEXT("authenticationKey"), AuthenticationKey);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);
	Serializer->WriteValue(TEXT("gameNotificationChannel"), GameNotificationChannel);
	Serializer->WriteValue(TEXT("subscribeKey"), SubscribeKey);
	Serializer->WriteValue(TEXT("playerChannel"), PlayerChannel);		
}

void USubscriberDetailsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	CustomChannelPrefix = Bag->GetStringField(TEXT("customChannelPrefix"));
	PlayerForRealmChannel = Bag->GetStringField(TEXT("playerForRealmChannel"));
	AuthenticationKey = Bag->GetStringField(TEXT("authenticationKey"));
	UBeamJsonUtils::DeserializeOptional<FString>("gameGlobalNotificationChannel", Bag, GameGlobalNotificationChannel, OuterOwner);
	GameNotificationChannel = Bag->GetStringField(TEXT("gameNotificationChannel"));
	SubscribeKey = Bag->GetStringField(TEXT("subscribeKey"));
	PlayerChannel = Bag->GetStringField(TEXT("playerChannel"));
}