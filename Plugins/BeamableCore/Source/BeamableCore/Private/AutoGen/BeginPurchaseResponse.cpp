
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UBeginPurchaseResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeginPurchaseResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access_token"), &AccessToken, Serializer);
}

void UBeginPurchaseResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access_token"), &AccessToken, Serializer);		
}

void UBeginPurchaseResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("txid")), Txid);
	UBeamJsonUtils::DeserializeOptional<FString>("access_token", Bag, AccessToken, OuterOwner);
}



