
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"
#include "Serialization/BeamJsonUtils.h"



void UOnlineStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOnlineStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("lastOnline"), &LastOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("online"), &bOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void UOnlineStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("lastOnline"), &LastOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("online"), &bOnline, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamPresenceStatus>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void UOnlineStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FDateTime>("lastOnline", Bag, LastOnline, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("online", Bag, bOnline, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamPresenceStatus>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



