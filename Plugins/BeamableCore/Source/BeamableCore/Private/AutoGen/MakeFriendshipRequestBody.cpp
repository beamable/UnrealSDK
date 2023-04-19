
#include "BeamableCore/Public/AutoGen/MakeFriendshipRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UMakeFriendshipRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void UMakeFriendshipRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void UMakeFriendshipRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("gamerTag")), GamerTag, OuterOwner);
}



