
#include "AutoGen/ObjectRequests.h"
#include "Serialization/BeamJsonUtils.h"


void UObjectRequests ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UObjectRequestBody*>, UObjectRequestBody*>(TEXT("request"), &Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);
}

void UObjectRequests::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UObjectRequestBody*>, UObjectRequestBody*>(TEXT("request"), &Request, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UObjectRequests ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UObjectRequestBody*>, UObjectRequestBody*>("request", Bag, Request, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("playerId", Bag, PlayerId, OuterOwner);
}