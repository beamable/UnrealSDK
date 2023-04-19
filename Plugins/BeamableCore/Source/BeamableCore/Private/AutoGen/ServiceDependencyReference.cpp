
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"





void UServiceDependencyReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);
}

void UServiceDependencyReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("storageType"), StorageType);		
}

void UServiceDependencyReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	StorageType = Bag->GetStringField(TEXT("storageType"));
}



