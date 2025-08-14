
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MyCoolNotification.h"





void UMyCoolNotification::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("FieldA"), FieldA, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("FieldB"), FieldB, Serializer);
}

void UMyCoolNotification::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("FieldA"), FieldA, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("FieldB"), FieldB, Serializer);		
}

void UMyCoolNotification::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FieldA"), Bag, FieldA);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FieldB"), Bag, FieldB);
}



