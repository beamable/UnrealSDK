
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceReferenceStreamData.generated.h"


UCLASS()
class UServiceReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ServiceName = {};
	UPROPERTY()
	FString Checksum = {};
	UPROPERTY()
	bool Enabled = {};
	UPROPERTY()
	FString ImageId = {};
	UPROPERTY()
	FString TemplateId = {};
	UPROPERTY()
	FString Comments = {};
	UPROPERTY()
	TArray<UServiceDependencyStreamData*> Dependencies = {};
	UPROPERTY()
	int64 ContainerHealthCheckPort = {};
	UPROPERTY()
	TArray<UServiceComponentStreamData*> Components = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("comments"), Comments);
		UBeamJsonUtils::SerializeArray<UServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		Serializer->WriteValue(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort);
		UBeamJsonUtils::SerializeArray<UServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("comments"), Comments);
		UBeamJsonUtils::SerializeArray<UServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		Serializer->WriteValue(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort);
		UBeamJsonUtils::SerializeArray<UServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceName = Bag->GetStringField(TEXT("serviceName"));
		Checksum = Bag->GetStringField(TEXT("checksum"));
		Enabled = Bag->GetBoolField(TEXT("enabled"));
		ImageId = Bag->GetStringField(TEXT("imageId"));
		TemplateId = Bag->GetStringField(TEXT("templateId"));
		Comments = Bag->GetStringField(TEXT("comments"));
		UBeamJsonUtils::DeserializeArray<UServiceDependencyStreamData*>(Bag->GetArrayField(TEXT("dependencies")), Dependencies, OuterOwner);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("containerHealthCheckPort")), ContainerHealthCheckPort);
		UBeamJsonUtils::DeserializeArray<UServiceComponentStreamData*>(Bag->GetArrayField(TEXT("components")), Components, OuterOwner);	
	}
};


