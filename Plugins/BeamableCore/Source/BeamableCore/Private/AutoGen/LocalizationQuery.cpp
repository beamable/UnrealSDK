
#include "BeamableCore/Public/AutoGen/LocalizationQuery.h"
#include "Serialization/BeamJsonUtils.h"




void ULocalizationQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("languages"), &Languages, Serializer);
}

void ULocalizationQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("languages"), &Languages, Serializer);		
}

void ULocalizationQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("languages", Bag, Languages, OuterOwner);
}



