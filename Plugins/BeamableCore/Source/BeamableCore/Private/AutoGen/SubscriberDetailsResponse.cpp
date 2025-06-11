
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("customChannelPrefix")), CustomChannelPrefix);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerForRealmChannel")), PlayerForRealmChannel);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("authenticationKey")), AuthenticationKey);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gameNotificationChannel")), GameNotificationChannel);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("subscribeKey")), SubscribeKey);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerChannel")), PlayerChannel);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("playerChannels")), PlayerChannels, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("gameGlobalNotificationChannel", Bag, GameGlobalNotificationChannel, OuterOwner);
}



