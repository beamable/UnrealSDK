
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceReference.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("enabled"), &bEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceComponent*>, UBeamoV2ServiceComponent*>(TEXT("components"), &Components, Serializer);
}

void UBeamoV2ServiceReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("enabled"), &bEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageId"), &ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("templateId"), &TemplateId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceComponent*>, UBeamoV2ServiceComponent*>(TEXT("components"), &Components, Serializer);		
}

void UBeamoV2ServiceReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("enabled", Bag, bEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageId", Bag, ImageId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("templateId", Bag, TemplateId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("containerHealthCheckPort", Bag, ContainerHealthCheckPort, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageCpuArch", Bag, ImageCpuArch, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceDependencyReference*>, UBeamoV2ServiceDependencyReference*>("dependencies", Bag, Dependencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceComponent*>, UBeamoV2ServiceComponent*>("components", Bag, Components, OuterOwner);
}



