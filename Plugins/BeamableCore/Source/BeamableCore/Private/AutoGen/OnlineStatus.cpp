
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"
#include "Serialization/BeamJsonUtils.h"



void UOnlineStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOnlineStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastOnline"), &LastOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("online"), &bOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<EPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void UOnlineStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lastOnline"), &LastOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("online"), &bOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<EPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void UOnlineStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("lastOnline", Bag, LastOnline, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("online", Bag, bOnline, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EPresenceStatus>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



