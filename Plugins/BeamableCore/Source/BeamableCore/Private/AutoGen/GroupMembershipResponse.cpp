
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGroupMembershipResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroupMembershipResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("member"), bMember);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void UGroupMembershipResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("member"), bMember);
	Serializer->WriteValue(TEXT("type"), UGroupTypeLibrary::GroupTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void UGroupMembershipResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bMember = Bag->GetBoolField(TEXT("member"));
	Type = UGroupTypeLibrary::SerializationNameToGroupType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeUObject<UGroupMetaData*>("group", Bag, Group, OuterOwner);
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
}



