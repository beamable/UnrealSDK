
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"





void UServiceDependencyReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
}

void UServiceDependencyReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);		
}

void UServiceDependencyReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageType"), Bag, StorageType);
}



