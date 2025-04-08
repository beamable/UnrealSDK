
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociation.h"





void UDeleteThirdPartyAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("thirdParty"), ThirdParty);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);
}

void UDeleteThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("thirdParty"), ThirdParty);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);		
}

void UDeleteThirdPartyAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("thirdParty")), ThirdParty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userAppId")), UserAppId);
}



