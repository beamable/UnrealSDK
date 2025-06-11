
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateResponse.h"





void UFacebookPaymentUpdateResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
}

void UFacebookPaymentUpdateResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);		
}

void UFacebookPaymentUpdateResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
}



