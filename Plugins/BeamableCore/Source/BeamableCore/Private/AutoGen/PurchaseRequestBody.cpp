
#include "BeamableCore/Public/AutoGen/PurchaseRequestBody.h"





void UPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
}

void UPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);		
}

void UPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PurchaseId = Bag->GetStringField(TEXT("purchaseId"));
}



