
#include "BeamableCore/Public/AutoGen/GroupInvite.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupInvite::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("useNewRewardsSystem"), &bUseNewRewardsSystem, Serializer);
}

void UGroupInvite::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("useNewRewardsSystem"), &bUseNewRewardsSystem, Serializer);		
}

void UGroupInvite::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("useNewRewardsSystem", Bag, bUseNewRewardsSystem, OuterOwner);
}



