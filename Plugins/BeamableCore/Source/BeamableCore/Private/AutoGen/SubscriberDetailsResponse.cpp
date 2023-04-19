
#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USubscriberDetailsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USubscriberDetailsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("customChannelPrefix"), CustomChannelPrefix);
	Serializer->WriteValue(TEXT("playerForRealmChannel"), PlayerForRealmChannel);
	Serializer->WriteValue(TEXT("authenticationKey"), AuthenticationKey);
	Serializer->WriteValue(TEXT("gameNotificationChannel"), GameNotificationChannel);
	Serializer->WriteValue(TEXT("subscribeKey"), SubscribeKey);
	Serializer->WriteValue(TEXT("playerChannel"), PlayerChannel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);
}

void USubscriberDetailsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("customChannelPrefix"), CustomChannelPrefix);
	Serializer->WriteValue(TEXT("playerForRealmChannel"), PlayerForRealmChannel);
	Serializer->WriteValue(TEXT("authenticationKey"), AuthenticationKey);
	Serializer->WriteValue(TEXT("gameNotificationChannel"), GameNotificationChannel);
	Serializer->WriteValue(TEXT("subscribeKey"), SubscribeKey);
	Serializer->WriteValue(TEXT("playerChannel"), PlayerChannel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);		
}

void USubscriberDetailsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	CustomChannelPrefix = Bag->GetStringField(TEXT("customChannelPrefix"));
	PlayerForRealmChannel = Bag->GetStringField(TEXT("playerForRealmChannel"));
	AuthenticationKey = Bag->GetStringField(TEXT("authenticationKey"));
	GameNotificationChannel = Bag->GetStringField(TEXT("gameNotificationChannel"));
	SubscribeKey = Bag->GetStringField(TEXT("subscribeKey"));
	PlayerChannel = Bag->GetStringField(TEXT("playerChannel"));
	UBeamJsonUtils::DeserializeOptional<FString>("gameGlobalNotificationChannel", Bag, GameGlobalNotificationChannel, OuterOwner);
}



