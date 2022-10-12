
#include "AutoGen/ServiceStorageStatus.h"



void UServiceStorageStatus ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
	Serializer->WriteValue(TEXT("isRunning"), bIsRunning);
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
}

void UServiceStorageStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
	Serializer->WriteValue(TEXT("isRunning"), bIsRunning);
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);		
}

void UServiceStorageStatus ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	StorageType = Bag->GetStringField(TEXT("storageType"));
	bIsRunning = Bag->GetBoolField(TEXT("isRunning"));
	bIsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
}