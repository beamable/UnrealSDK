
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestNotificationRequestArgs.h"





void UTestNotificationRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);
}

void UTestNotificationRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("a"), A, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("b"), B, Serializer);		
}

void UTestNotificationRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("a"), Bag, A);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("b"), Bag, B);
}



