
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
	UBeamJsonUtils::SerializeArray<FString>(TEXT("playerChannels"), PlayerChannels, Serializer);
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



