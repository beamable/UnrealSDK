
#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UCancelPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);
}

void UCancelPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);		
}

void UCancelPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("txid"), Bag, Txid);
}



