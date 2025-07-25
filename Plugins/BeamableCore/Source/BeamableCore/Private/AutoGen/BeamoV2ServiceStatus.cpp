
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStatus.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("running"), &bRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);
}

void UBeamoV2ServiceStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("running"), &bRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);		
}

void UBeamoV2ServiceStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isCurrent", Bag, bIsCurrent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("running", Bag, bRunning, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageId", Bag, ImageId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>("serviceDependencyReferences", Bag, ServiceDependencyReferences, OuterOwner);
}



