
#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USubscriberDetailsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USubscriberDetailsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customChannelPrefix"), CustomChannelPrefix, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerForRealmChannel"), PlayerForRealmChannel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("authenticationKey"), AuthenticationKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameNotificationChannel"), GameNotificationChannel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("subscribeKey"), SubscribeKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerChannel"), PlayerChannel, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("playerChannels"), PlayerChannels, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);
}

void USubscriberDetailsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customChannelPrefix"), CustomChannelPrefix, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerForRealmChannel"), PlayerForRealmChannel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("authenticationKey"), AuthenticationKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameNotificationChannel"), GameNotificationChannel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("subscribeKey"), SubscribeKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerChannel"), PlayerChannel, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("playerChannels"), PlayerChannels, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameGlobalNotificationChannel"), &GameGlobalNotificationChannel, Serializer);		
}

void USubscriberDetailsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("customChannelPrefix"), Bag, CustomChannelPrefix);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerForRealmChannel"), Bag, PlayerForRealmChannel);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("authenticationKey"), Bag, AuthenticationKey);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gameNotificationChannel"), Bag, GameNotificationChannel);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("subscribeKey"), Bag, SubscribeKey);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerChannel"), Bag, PlayerChannel);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("playerChannels"), Bag, PlayerChannels, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("gameGlobalNotificationChannel", Bag, GameGlobalNotificationChannel, OuterOwner);
}



