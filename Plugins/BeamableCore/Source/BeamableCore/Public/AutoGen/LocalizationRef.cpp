
#include "AutoGen/LocalizationRef.h"
#include "Serialization/BeamJsonUtils.h"


void ULocalizationRef ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("localizationId"), LocalizationId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);
}

void ULocalizationRef::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("localizationId"), LocalizationId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);		
}

void ULocalizationRef ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LocalizationId = Bag->GetStringField(TEXT("localizationId"));
	UBeamJsonUtils::DeserializeOptional<FString>("defaultValue", Bag, DefaultValue, OuterOwner);
	bEmpty = Bag->GetBoolField(TEXT("empty"));
}