
#include "BeamableCore/Public/AutoGen/ServiceReference.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("arm"), bArm, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceComponent*>, UServiceComponent*>(TEXT("components"), &Components, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
}

void UServiceReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("arm"), bArm, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), bEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceComponent*>, UServiceComponent*>(TEXT("components"), &Components, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);		
}

void UServiceReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("archived"), Bag, bArchived);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("arm"), Bag, bArm);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enabled"), Bag, bEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("templateId"), Bag, TemplateId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("imageId"), Bag, ImageId);
	UBeamJsonUtils::DeserializeOptional<int64>("containerHealthCheckPort", Bag, ContainerHealthCheckPort, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageCpuArch", Bag, ImageCpuArch, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceComponent*>, UServiceComponent*>("components", Bag, Components, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("dependencies", Bag, Dependencies, OuterOwner);
}



