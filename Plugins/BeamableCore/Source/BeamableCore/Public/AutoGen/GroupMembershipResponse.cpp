
#include "AutoGen/GroupMembershipResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGroupMembershipResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	Serializer->WriteValue(TEXT("member"), bMember);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
}

void UGroupMembershipResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	Serializer->WriteValue(TEXT("member"), bMember);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);		
}

void UGroupMembershipResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	bMember = Bag->GetBoolField(TEXT("member"));
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UGroupMetaData*>("group", Bag, Group, OuterOwner);
}