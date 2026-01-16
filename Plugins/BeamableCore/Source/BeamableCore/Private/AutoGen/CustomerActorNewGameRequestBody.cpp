
#include "BeamableCore/Public/AutoGen/CustomerActorNewGameRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerActorNewGameRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isHidden"), &bIsHidden, Serializer);
}

void UCustomerActorNewGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isHidden"), &bIsHidden, Serializer);		
}

void UCustomerActorNewGameRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gameName"), Bag, GameName);
	UBeamJsonUtils::DeserializeOptional<bool>("isHidden", Bag, bIsHidden, OuterOwner);
}



