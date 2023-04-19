
#include "BeamableCore/Public/AutoGen/RegisterReq.h"





void URegisterReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider"), Provider);
	Serializer->WriteValue(TEXT("token"), Token);
}

void URegisterReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider"), Provider);
	Serializer->WriteValue(TEXT("token"), Token);		
}

void URegisterReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Provider = Bag->GetStringField(TEXT("provider"));
	Token = Bag->GetStringField(TEXT("token"));
}



