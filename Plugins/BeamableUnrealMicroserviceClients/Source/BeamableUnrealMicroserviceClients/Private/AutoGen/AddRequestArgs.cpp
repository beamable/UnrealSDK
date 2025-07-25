
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AddRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UAddRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);
}

void UAddRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);		
}

void UAddRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("a"), Bag, A);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("b"), Bag, B);
}



