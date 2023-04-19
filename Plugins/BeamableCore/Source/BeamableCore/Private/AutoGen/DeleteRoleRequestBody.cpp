
#include "BeamableCore/Public/AutoGen/DeleteRoleRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDeleteRoleRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realm"), &Realm, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);
}

void UDeleteRoleRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realm"), &Realm, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("role"), &Role, Serializer);		
}

void UDeleteRoleRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realm", Bag, Realm, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("role", Bag, Role, OuterOwner);
}



