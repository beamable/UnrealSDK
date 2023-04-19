
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
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("txid")), Txid);
	Reason = Bag->GetStringField(TEXT("reason"));
}



