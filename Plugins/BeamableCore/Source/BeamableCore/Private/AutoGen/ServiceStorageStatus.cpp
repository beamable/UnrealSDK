
#include "BeamableCore/Public/AutoGen/ServiceStorageStatus.h"





void UServiceStorageStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRunning"), bIsRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
}

void UServiceStorageStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRunning"), bIsRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);		
}

void UServiceStorageStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isCurrent"), Bag, bIsCurrent);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isRunning"), Bag, bIsRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageType"), Bag, StorageType);
}



