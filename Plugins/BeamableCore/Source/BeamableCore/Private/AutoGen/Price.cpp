
#include "BeamableCore/Public/AutoGen/Price.h"
#include "Serialization/BeamJsonUtils.h"




void UPrice::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("amount"), &Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int32>, int32>(TEXT("schedule"), &Schedule, Serializer);
}

void UPrice::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("amount"), &Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int32>, int32>(TEXT("schedule"), &Schedule, Serializer);		
}

void UPrice::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeOptional<int32>("amount", Bag, Amount, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<int32>, int32>("schedule", Bag, Schedule, OuterOwner);
}



