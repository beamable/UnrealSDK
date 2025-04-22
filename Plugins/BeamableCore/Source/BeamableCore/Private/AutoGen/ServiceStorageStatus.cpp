
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isCurrent")), bIsCurrent);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isRunning")), bIsRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageType")), StorageType);
}



