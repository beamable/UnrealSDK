
#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UCancelPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
}

void UCancelPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);		
}

void UCancelPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("txid")), Txid);
}



