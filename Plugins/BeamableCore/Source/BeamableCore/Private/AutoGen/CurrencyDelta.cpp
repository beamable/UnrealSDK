
#include "BeamableCore/Public/AutoGen/CurrencyDelta.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrencyDelta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("before"), Before, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("after"), After, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>(TEXT("properties"), &Properties, Serializer);
}

void UCurrencyDelta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("before"), Before, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("after"), After, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>(TEXT("properties"), &Properties, Serializer);		
}

void UCurrencyDelta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("before"), Bag, Before);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("after"), Bag, After);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>("properties", Bag, Properties, OuterOwner);
}



