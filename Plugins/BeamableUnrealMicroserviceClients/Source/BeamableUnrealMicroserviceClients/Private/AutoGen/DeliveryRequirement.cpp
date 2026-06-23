
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryRequirement.h"

#include "Misc/DefaultValueHelper.h"



void UDeliveryRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("propertyName"), PropertyName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("comparison"), Comparison, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
}

void UDeliveryRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("propertyName"), PropertyName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("comparison"), Comparison, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);		
}

void UDeliveryRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("propertyName"), Bag, PropertyName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("comparison"), Bag, Comparison);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("value"), Bag, Value);
}



