
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
	bIsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
	bIsRunning = Bag->GetBoolField(TEXT("isRunning"));
	Id = Bag->GetStringField(TEXT("id"));
	StorageType = Bag->GetStringField(TEXT("storageType"));
}



