
#include "BeamableCore/Public/AutoGen/SendFriendRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USendFriendRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void USendFriendRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void USendFriendRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("gamerTag")), GamerTag, OuterOwner);
}



