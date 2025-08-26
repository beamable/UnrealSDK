
#include "BeamableCore/Public/AutoGen/RoleChangeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URoleChangeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void URoleChangeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void URoleChangeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("role"), Bag, Role);
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



