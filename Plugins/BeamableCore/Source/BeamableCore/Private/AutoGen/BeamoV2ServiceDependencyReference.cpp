
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceDependencyReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceDependencyReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);
}

void UBeamoV2ServiceDependencyReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);		
}

void UBeamoV2ServiceDependencyReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageType", Bag, StorageType, OuterOwner);
}



