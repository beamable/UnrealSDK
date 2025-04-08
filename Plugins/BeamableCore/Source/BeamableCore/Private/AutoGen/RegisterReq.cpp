
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("provider")), Provider);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);
}



