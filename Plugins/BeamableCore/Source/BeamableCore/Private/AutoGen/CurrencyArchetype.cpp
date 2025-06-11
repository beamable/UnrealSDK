
#include "BeamableCore/Public/AutoGen/CurrencyArchetype.h"
#include "Serialization/BeamJsonUtils.h"




void UCurrencyArchetype::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startingAmount"), &StartingAmount, Serializer);
}

void UCurrencyArchetype::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startingAmount"), &StartingAmount, Serializer);		
}

void UCurrencyArchetype::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeOptional<UFederationInfo*>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("clientPermission", Bag, ClientPermission, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startingAmount", Bag, StartingAmount, OuterOwner);
}



