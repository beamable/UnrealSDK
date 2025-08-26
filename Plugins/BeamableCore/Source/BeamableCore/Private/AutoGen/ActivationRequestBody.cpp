
#include "BeamableCore/Public/AutoGen/ActivationRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UActivationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);
}

void UActivationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);		
}

void UActivationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cid"), Bag, Cid);
}



