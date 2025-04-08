
#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UFailPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("reason"), Reason);
}

void UFailPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("reason"), Reason);		
}

void UFailPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("txid")), Txid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("reason")), Reason);
}



