
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/CliServiceDependencyStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceComponentStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "CliServiceReferenceStreamData.generated.h"


UCLASS(BlueprintType)
class UCliServiceReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Enabled = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImageId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TemplateId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Comments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCliServiceDependencyStreamData*> Dependencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ContainerHealthCheckPort = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCliServiceComponentStreamData*> Components = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("comments"), Comments, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("imageId"), ImageId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("comments"), Comments, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enabled"), Bag, Enabled);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("imageId"), Bag, ImageId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("templateId"), Bag, TemplateId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("comments"), Bag, Comments);
		UBeamJsonUtils::DeserializeArray<UCliServiceDependencyStreamData*>(TEXT("dependencies"), Bag, Dependencies, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("containerHealthCheckPort"), Bag, ContainerHealthCheckPort);
		UBeamJsonUtils::DeserializeArray<UCliServiceComponentStreamData*>(TEXT("components"), Bag, Components, OuterOwner);	
	}
};


