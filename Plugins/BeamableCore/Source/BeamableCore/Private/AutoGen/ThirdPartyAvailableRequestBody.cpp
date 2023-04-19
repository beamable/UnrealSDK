
#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBody.h"





void UThirdPartyAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("thirdParty"), ThirdParty);
	Serializer->WriteValue(TEXT("token"), Token);
}

void UThirdPartyAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("thirdParty"), ThirdParty);
	Serializer->WriteValue(TEXT("token"), Token);		
}

void UThirdPartyAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ThirdParty = Bag->GetStringField(TEXT("thirdParty"));
	Token = Bag->GetStringField(TEXT("token"));
}



