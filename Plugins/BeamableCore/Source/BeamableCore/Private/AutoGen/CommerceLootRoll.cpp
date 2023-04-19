
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
	bPreroll = Bag->GetBoolField(TEXT("preroll"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("externalTables", Bag, ExternalTables, OuterOwner);
}



