
#include "BeamableCore/Public/AutoGen/BeamoV2GetStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2GetStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2GetStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStatus*>, UBeamoV2ServiceStatus*>(TEXT("services"), &Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageStatus*>, UBeamoV2ServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);
}

void UBeamoV2GetStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStatus*>, UBeamoV2ServiceStatus*>(TEXT("services"), &Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceStorageStatus*>, UBeamoV2ServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);		
}

void UBeamoV2GetStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isCurrent", Bag, bIsCurrent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceStatus*>, UBeamoV2ServiceStatus*>("services", Bag, Services, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceStorageStatus*>, UBeamoV2ServiceStorageStatus*>("storageStatuses", Bag, StorageStatuses, OuterOwner);
}



