
#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBody.h"





void UVerifyPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receipt"), Receipt);
}

void UVerifyPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receipt"), Receipt);		
}

void UVerifyPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("receipt")), Receipt);
}



