
#include "BeamableCore/Public/AutoGen/VerifyReceiptRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UVerifyReceiptRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("receipt"), &Receipt, Serializer);
}

void UVerifyReceiptRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("receipt"), &Receipt, Serializer);		
}

void UVerifyReceiptRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("provider", Bag, Provider, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("receipt", Bag, Receipt, OuterOwner);
}



