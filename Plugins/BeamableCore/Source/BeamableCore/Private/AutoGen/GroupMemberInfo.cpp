
#include "BeamableCore/Public/AutoGen/GroupMemberInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupMemberInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>(TEXT("guild"), &Guild, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>(TEXT("subgroup"), &Subgroup, Serializer);
}

void UGroupMemberInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>(TEXT("guild"), &Guild, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>(TEXT("subgroup"), &Subgroup, Serializer);		
}

void UGroupMemberInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>("guild", Bag, Guild, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupUserMember*>, UGroupUserMember*>("subgroup", Bag, Subgroup, OuterOwner);
}



