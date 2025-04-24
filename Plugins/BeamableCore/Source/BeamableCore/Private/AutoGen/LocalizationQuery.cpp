
#include "BeamableCore/Public/AutoGen/LocalizationQuery.h"
#include "Serialization/BeamJsonUtils.h"




void ULocalizationQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("languages"), &Languages, Serializer);
}

void ULocalizationQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("languages"), &Languages, Serializer);		
}

void ULocalizationQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("languages", Bag, Languages, OuterOwner);
}



