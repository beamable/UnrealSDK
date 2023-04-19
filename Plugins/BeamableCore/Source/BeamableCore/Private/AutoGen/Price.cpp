
#include "BeamableCore/Public/AutoGen/Price.h"
#include "Serialization/BeamJsonUtils.h"




void UPrice::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("amount"), &Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int32>, int32>(TEXT("schedule"), &Schedule, Serializer);
}

void UPrice::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("amount"), &Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int32>, int32>(TEXT("schedule"), &Schedule, Serializer);		
}

void UPrice::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Type = Bag->GetStringField(TEXT("type"));
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<int32>("amount", Bag, Amount, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<int32>, int32>("schedule", Bag, Schedule, OuterOwner);
}



