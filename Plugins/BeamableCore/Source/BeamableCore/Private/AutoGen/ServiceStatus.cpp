
#include "BeamableCore/Public/AutoGen/ServiceStatus.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("running"), &bRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);
}

void UServiceStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isCurrent"), &bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("running"), &bRunning, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);		
}

void UServiceStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isCurrent", Bag, bIsCurrent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("running", Bag, bRunning, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageId", Bag, ImageId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("serviceDependencyReferences", Bag, ServiceDependencyReferences, OuterOwner);
}



