
#include "BeamableCore/Public/AutoGen/NotificationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UNotificationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UNotificationRequestData*>("payload", Payload, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("useSignalWhenPossible"), &bUseSignalWhenPossible, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customChannelSuffix"), &CustomChannelSuffix, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("dbid"), &Dbid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("dbids"), &Dbids, Serializer);
}

void UNotificationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UNotificationRequestData*>("payload", Payload, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("useSignalWhenPossible"), &bUseSignalWhenPossible, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customChannelSuffix"), &CustomChannelSuffix, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("dbid"), &Dbid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("dbids"), &Dbids, Serializer);		
}

void UNotificationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UNotificationRequestData*>("payload", Bag, Payload, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("useSignalWhenPossible", Bag, bUseSignalWhenPossible, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customChannelSuffix", Bag, CustomChannelSuffix, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("dbid", Bag, Dbid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<int64>, int64>("dbids", Bag, Dbids, OuterOwner);
}



