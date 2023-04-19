
#include "BeamableCore/Public/AutoGen/RoleChangeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URoleChangeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("role"), Role);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void URoleChangeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("role"), Role);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void URoleChangeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	Role = Bag->GetStringField(TEXT("role"));
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



