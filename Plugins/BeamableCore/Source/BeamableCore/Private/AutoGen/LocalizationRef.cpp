
#include "BeamableCore/Public/AutoGen/LocalizationRef.h"
#include "Serialization/BeamJsonUtils.h"




void ULocalizationRef::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("empty"), bEmpty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizationId"), LocalizationId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);
}

void ULocalizationRef::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("empty"), bEmpty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizationId"), LocalizationId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("defaultValue"), &DefaultValue, Serializer);		
}

void ULocalizationRef::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("empty")), bEmpty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("localizationId")), LocalizationId);
	UBeamJsonUtils::DeserializeOptional<FString>("defaultValue", Bag, DefaultValue, OuterOwner);
}



