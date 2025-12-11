
#include "BeamableCore/Public/AutoGen/PartyMemberTags.h"
#include "Serialization/BeamJsonUtils.h"




void UPartyMemberTags::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("memberTags"), &MemberTags, Serializer);
}

void UPartyMemberTags::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("memberTags"), &MemberTags, Serializer);		
}

void UPartyMemberTags::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("memberTags", Bag, MemberTags, OuterOwner);
}



