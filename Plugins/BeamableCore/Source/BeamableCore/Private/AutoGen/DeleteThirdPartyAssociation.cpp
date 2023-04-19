
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
	ThirdParty = Bag->GetStringField(TEXT("thirdParty"));
	UserAppId = Bag->GetStringField(TEXT("userAppId"));
}



