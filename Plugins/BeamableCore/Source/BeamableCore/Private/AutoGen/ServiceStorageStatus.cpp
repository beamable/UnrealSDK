
#include "BeamableCore/Public/AutoGen/ServiceStorageStatus.h"





void UServiceStorageStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	Serializer->WriteValue(TEXT("isRunning"), bIsRunning);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
}

void UServiceStorageStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	Serializer->WriteValue(TEXT("isRunning"), bIsRunning);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);		
}

void UServiceStorageStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isCurrent")), bIsCurrent);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isRunning")), bIsRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageType")), StorageType);
}



