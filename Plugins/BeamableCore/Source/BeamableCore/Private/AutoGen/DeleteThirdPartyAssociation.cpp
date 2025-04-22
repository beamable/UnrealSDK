
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("thirdParty")), ThirdParty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userAppId")), UserAppId);
}



