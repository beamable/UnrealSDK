
#include "BeamableCore/Public/AutoGen/ServiceStatus.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	Serializer->WriteValue(TEXT("running"), bRunning);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);
}

void UServiceStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	Serializer->WriteValue(TEXT("running"), bRunning);
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("imageId"), ImageId);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>(TEXT("serviceDependencyReferences"), &ServiceDependencyReferences, Serializer);		
}

void UServiceStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
	bRunning = Bag->GetBoolField(TEXT("running"));
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	ImageId = Bag->GetStringField(TEXT("imageId"));
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceDependencyReference*>, UServiceDependencyReference*>("serviceDependencyReferences", Bag, ServiceDependencyReferences, OuterOwner);
}



