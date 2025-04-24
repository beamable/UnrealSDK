
#include "BeamableCore/Public/AutoGen/GroupUserMember.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupUserMember::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("joined"), &Joined, Serializer);
}

void UGroupUserMember::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("joined"), &Joined, Serializer);		
}

void UGroupUserMember::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeArray<UGroupUserMember*>(Bag->GetArrayField(TEXT("subGroups")), SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("joined", Bag, Joined, OuterOwner);
}



