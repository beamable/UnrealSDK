
#include "BeamableCore/Public/AutoGen/PurchaseRequestBody.h"





void UPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);
}

void UPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);		
}

void UPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("purchaseId")), PurchaseId);
}



