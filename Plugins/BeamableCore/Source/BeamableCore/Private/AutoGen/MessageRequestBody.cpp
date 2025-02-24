
#include "BeamableCore/Public/AutoGen/MessageRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UMessageRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("channel"), &Channel, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
}

void UMessageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("channel"), &Channel, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);		
}

void UMessageRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("pid", Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("channel", Bag, Channel, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
}



