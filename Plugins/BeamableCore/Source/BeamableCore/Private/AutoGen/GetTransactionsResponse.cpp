
#include "BeamableCore/Public/AutoGen/GetTransactionsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetTransactionsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetTransactionsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTransaction*>, UTransaction*>(TEXT("transactions"), &Transactions, Serializer);
}

void UGetTransactionsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UTransaction*>, UTransaction*>(TEXT("transactions"), &Transactions, Serializer);		
}

void UGetTransactionsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UTransaction*>, UTransaction*>("transactions", Bag, Transactions, OuterOwner);
}



