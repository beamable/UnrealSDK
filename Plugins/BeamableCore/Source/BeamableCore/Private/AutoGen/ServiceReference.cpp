
#include "BeamableCore/Public/AutoGen/ServiceReference.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("arm"), bArm);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("templateId"), TemplateId);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceComponent*>, UServiceComponent*>(TEXT("components"), &Components, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);
}

void UServiceReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("arm"), bArm);
	Serializer->WriteValue(TEXT("enabled"), bEnabled);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("templateId"), TemplateId);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("containerHealthCheckPort"), &ContainerHealthCheckPort, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("imageCpuArch"), &ImageCpuArch, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceComponent*>, UServiceComponent*>(TEXT("components"), &Components, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("dependencies"), &Dependencies, Serializer);		
}

void UServiceReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bArchived = Bag->GetBoolField(TEXT("archived"));
	bArm = Bag->GetBoolField(TEXT("arm"));
	bEnabled = Bag->GetBoolField(TEXT("enabled"));
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	Checksum = Bag->GetStringField(TEXT("checksum"));
	TemplateId = Bag->GetStringField(TEXT("templateId"));
	ImageId = Bag->GetStringField(TEXT("imageId"));
	UBeamJsonUtils::DeserializeOptional<int64>("containerHealthCheckPort", Bag, ContainerHealthCheckPort, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("imageCpuArch", Bag, ImageCpuArch, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceComponent*>, UServiceComponent*>("components", Bag, Components, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("dependencies", Bag, Dependencies, OuterOwner);
}



