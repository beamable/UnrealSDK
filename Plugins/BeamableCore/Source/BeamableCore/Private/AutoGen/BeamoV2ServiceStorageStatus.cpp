
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageStatus.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceStorageStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isRunning"), &bIsRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);
}

void UBeamoV2ServiceStorageStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isRunning"), &bIsRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("storageType"), &StorageType, Serializer);		
}

void UBeamoV2ServiceStorageStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isCurrent", Bag, bIsCurrent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("isRunning", Bag, bIsRunning, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("storageType", Bag, StorageType, OuterOwner);
}



