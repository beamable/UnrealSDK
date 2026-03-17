
#include "BeamableCore/Public/AutoGen/PlayerSessionActorPaymentTotal.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerSessionActorPaymentTotal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currency"), &Currency, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("amount"), &Amount, Serializer);
}

void UPlayerSessionActorPaymentTotal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currency"), &Currency, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("amount"), &Amount, Serializer);		
}

void UPlayerSessionActorPaymentTotal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("currency", Bag, Currency, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("amount", Bag, Amount, OuterOwner);
}



