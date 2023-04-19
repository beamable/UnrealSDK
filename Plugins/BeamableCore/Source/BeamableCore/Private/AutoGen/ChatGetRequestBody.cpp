
#include "BeamableCore/Public/AutoGen/ChatGetRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UChatGetRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
}

void UChatGetRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);		
}

void UChatGetRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
}



