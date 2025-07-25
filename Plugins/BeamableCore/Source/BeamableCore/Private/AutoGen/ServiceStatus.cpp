
#include "BeamableCore/Public/AutoGen/ServiceStatus.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);
}

void UServiceStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);		
}

void UServiceStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isCurrent"), Bag, bIsCurrent);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("running"), Bag, bRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("imageId"), Bag, ImageId);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("serviceDependencyReferences", Bag, ServiceDependencyReferences, OuterOwner);
}



