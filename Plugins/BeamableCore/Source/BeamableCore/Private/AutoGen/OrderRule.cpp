
#include "BeamableCore/Public/AutoGen/OrderRule.h"

#include "Misc/DefaultValueHelper.h"



void UOrderRule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("v"), V);
	Serializer->WriteValue(TEXT("o"), O);
}

void UOrderRule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("v"), V);
	Serializer->WriteValue(TEXT("o"), O);		
}

void UOrderRule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("v")), V);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("o")), O);
}



