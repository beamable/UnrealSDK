
#include "BeamableCore/Public/AutoGen/GroupMembershipRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupMembershipRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("group"), Group);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("successor"), &Successor, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void UGroupMembershipRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	Serializer->WriteValue(TEXT("group"), Group);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("successor"), &Successor, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void UGroupMembershipRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("group")), Group);
	UBeamJsonUtils::DeserializeOptional<int64>("successor", Bag, Successor, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("score", Bag, Score, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



