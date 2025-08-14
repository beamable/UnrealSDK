
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestArrRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UTestArrRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);
}

void UTestArrRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);		
}

void UTestArrRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("a"), Bag, A);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("b"), Bag, B);
}



