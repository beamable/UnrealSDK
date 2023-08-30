
#include "BeamableCore/Public/AutoGen/CurrencyArchetype.h"
#include "Serialization/BeamJsonUtils.h"




void UCurrencyArchetype::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startingAmount"), &StartingAmount, Serializer);
}

void UCurrencyArchetype::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startingAmount"), &StartingAmount, Serializer);		
}

void UCurrencyArchetype::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<UArchetypeProxy*>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("clientPermission", Bag, ClientPermission, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startingAmount", Bag, StartingAmount, OuterOwner);
}



