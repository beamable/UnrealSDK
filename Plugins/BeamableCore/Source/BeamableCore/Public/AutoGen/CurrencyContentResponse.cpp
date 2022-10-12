
#include "AutoGen/CurrencyContentResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UCurrencyContentResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyArchetype*>(TEXT("content"), Content, Serializer);
}

void UCurrencyContentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyArchetype*>(TEXT("content"), Content, Serializer);		
}

void UCurrencyContentResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCurrencyArchetype*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}