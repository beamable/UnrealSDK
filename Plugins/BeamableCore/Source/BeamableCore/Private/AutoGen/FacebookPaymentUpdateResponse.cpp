
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateResponse.h"





void UFacebookPaymentUpdateResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
}

void UFacebookPaymentUpdateResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);		
}

void UFacebookPaymentUpdateResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
}



