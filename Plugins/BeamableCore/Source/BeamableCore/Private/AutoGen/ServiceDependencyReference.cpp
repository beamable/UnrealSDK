
#include "BeamableCore/Public/AutoGen/ServiceDependencyReference.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceDependencyReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);
}

void UServiceDependencyReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);		
}

void UServiceDependencyReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageType", Bag, StorageType, OuterOwner);
}



