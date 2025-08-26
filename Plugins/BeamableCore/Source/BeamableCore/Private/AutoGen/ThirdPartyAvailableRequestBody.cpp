
#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBody.h"





void UThirdPartyAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("thirdParty"), ThirdParty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
}

void UThirdPartyAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("thirdParty"), ThirdParty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);		
}

void UThirdPartyAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("thirdParty"), Bag, ThirdParty);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
}



