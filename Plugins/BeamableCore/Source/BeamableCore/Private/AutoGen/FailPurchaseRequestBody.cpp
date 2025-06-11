
#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UFailPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("reason"), Reason, Serializer);
}

void UFailPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("reason"), Reason, Serializer);		
}

void UFailPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("txid")), Txid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("reason")), Reason);
}



