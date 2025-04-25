
#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBody.h"





void UVerifyPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);
}

void UVerifyPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);		
}

void UVerifyPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("receipt")), Receipt);
}



