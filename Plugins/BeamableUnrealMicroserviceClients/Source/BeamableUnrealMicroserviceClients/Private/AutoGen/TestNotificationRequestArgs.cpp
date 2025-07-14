
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("a")), A);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("b")), B);
}



