
#include "BeamableCore/Public/AutoGen/CommerceLootRoll.h"
#include "Serialization/BeamJsonUtils.h"




void UCommerceLootRoll::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("preroll"), bPreroll);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("externalTables"), &ExternalTables, Serializer);
}

void UCommerceLootRoll::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("preroll"), bPreroll);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("externalTables"), &ExternalTables, Serializer);		
}

void UCommerceLootRoll::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("preroll")), bPreroll);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("externalTables", Bag, ExternalTables, OuterOwner);
}



