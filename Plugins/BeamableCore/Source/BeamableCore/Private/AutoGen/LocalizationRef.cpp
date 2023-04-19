
#include "BeamableCore/Public/AutoGen/LocalizationRef.h"
#include "Serialization/BeamJsonUtils.h"




void ULocalizationRef::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	Serializer->WriteValue(TEXT("localizationId"), LocalizationId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);
}

void ULocalizationRef::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	Serializer->WriteValue(TEXT("localizationId"), LocalizationId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);		
}

void ULocalizationRef::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bEmpty = Bag->GetBoolField(TEXT("empty"));
	LocalizationId = Bag->GetStringField(TEXT("localizationId"));
	UBeamJsonUtils::DeserializeOptional<FString>("defaultValue", Bag, DefaultValue, OuterOwner);
}



