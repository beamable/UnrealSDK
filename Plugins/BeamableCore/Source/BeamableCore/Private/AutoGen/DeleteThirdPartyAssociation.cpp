
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociation.h"





void UDeleteThirdPartyAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("thirdParty"), ThirdParty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userAppId"), UserAppId, Serializer);
}

void UDeleteThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("thirdParty"), ThirdParty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("userAppId"), UserAppId, Serializer);		
}

void UDeleteThirdPartyAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("thirdParty"), Bag, ThirdParty);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("userAppId"), Bag, UserAppId);
}



