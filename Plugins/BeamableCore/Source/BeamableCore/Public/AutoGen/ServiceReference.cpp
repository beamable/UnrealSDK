
#include "AutoGen/ServiceReference.h"
#include "Serialization/BeamJsonUtils.h"


void UServiceReference ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("arm"), bArm);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("templateId"), TemplateId);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
}

void UServiceReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("arm"), bArm);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("templateId"), TemplateId);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);		
}

void UServiceReference ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("containerHealthCheckPort", Bag, ContainerHealthCheckPort, OuterOwner);
	bArchived = Bag->GetBoolField(TEXT("archived"));
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	bEnabled = Bag->GetBoolField(TEXT("enabled"));
	bArm = Bag->GetBoolField(TEXT("arm"));
	Checksum = Bag->GetStringField(TEXT("checksum"));
	TemplateId = Bag->GetStringField(TEXT("templateId"));
	ImageId = Bag->GetStringField(TEXT("imageId"));
	UBeamJsonUtils::DeserializeOptional<FString>("imageCpuArch", Bag, ImageCpuArch, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("dependencies", Bag, Dependencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
}