
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGroupMembershipResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroupMembershipResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("member"), bMember, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void UGroupMembershipResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("member"), bMember, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeUObject<UGroupMetaData*>("group", Group, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void UGroupMembershipResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("member")), bMember);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeUObject<UGroupMetaData*>("group", Bag, Group, OuterOwner);
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
}



