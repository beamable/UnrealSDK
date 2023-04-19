
#include "BeamableCore/Public/AutoGen/NotificationRequestData.h"
#include "Serialization/BeamJsonUtils.h"




void UNotificationRequestData::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("channel"), &Channel, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("messageKey"), &MessageKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("messageFull"), &MessageFull, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageParams"), &MessageParams, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("meta"), &Meta, Serializer);
}

void UNotificationRequestData::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("channel"), &Channel, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("messageKey"), &MessageKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("messageFull"), &MessageFull, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageParams"), &MessageParams, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("meta"), &Meta, Serializer);		
}

void UNotificationRequestData::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("channel", Bag, Channel, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("messageKey", Bag, MessageKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("context", Bag, Context, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("messageFull", Bag, MessageFull, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageParams", Bag, MessageParams, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("meta", Bag, Meta, OuterOwner);
}



