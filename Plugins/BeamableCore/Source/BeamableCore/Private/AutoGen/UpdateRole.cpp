
#include "BeamableCore/Public/AutoGen/UpdateRole.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateRole::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realm"), &Realm, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);
}

void UUpdateRole::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realm"), &Realm, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);		
}

void UUpdateRole::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realm", Bag, Realm, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("role", Bag, Role, OuterOwner);
}



