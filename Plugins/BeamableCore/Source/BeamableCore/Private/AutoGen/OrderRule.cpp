
#include "BeamableCore/Public/AutoGen/OrderRule.h"

#include "Misc/DefaultValueHelper.h"



void UOrderRule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("v"), V, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("o"), O, Serializer);
}

void UOrderRule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("v"), V, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("o"), O, Serializer);		
}

void UOrderRule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("v")), V);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("o")), O);
}



