
#include "BeamableCore/Public/AutoGen/OfferDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UOfferDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("titles"), Titles, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("images"), Images, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("descriptions"), Descriptions, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("obtain"), Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<UCommerceLootRoll*>(TEXT("lootRoll"), &LootRoll, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("metadata"), &Metadata, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);
}

void UOfferDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("titles"), Titles, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("images"), Images, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("descriptions"), Descriptions, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("obtain"), Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<UCommerceLootRoll*>(TEXT("lootRoll"), &LootRoll, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("metadata"), &Metadata, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);		
}

void UOfferDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("titles")), Titles, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("images")), Images, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("descriptions")), Descriptions, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("obtain")), Obtain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UCommerceLootRoll*>("lootRoll", Bag, LootRoll, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("metadata", Bag, Metadata, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("obtainItems", Bag, ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>("obtainCurrency", Bag, ObtainCurrency, OuterOwner);
}



