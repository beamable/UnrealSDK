
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
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("comments"), Comments);
		UBeamJsonUtils::SerializeArray<UCliServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		Serializer->WriteValue(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort);
		UBeamJsonUtils::SerializeArray<UCliServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("comments"), Comments);
		UBeamJsonUtils::SerializeArray<UCliServiceDependencyStreamData*>(TEXT("dependencies"), Dependencies, Serializer);
		Serializer->WriteValue(TEXT("containerHealthCheckPort"), ContainerHealthCheckPort);
		UBeamJsonUtils::SerializeArray<UCliServiceComponentStreamData*>(TEXT("components"), Components, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceName = Bag->GetStringField(TEXT("serviceName"));
		Checksum = Bag->GetStringField(TEXT("checksum"));
		Enabled = Bag->GetBoolField(TEXT("enabled"));
		ImageId = Bag->GetStringField(TEXT("imageId"));
		TemplateId = Bag->GetStringField(TEXT("templateId"));
		Comments = Bag->GetStringField(TEXT("comments"));
		UBeamJsonUtils::DeserializeArray<UCliServiceDependencyStreamData*>(Bag->GetArrayField(TEXT("dependencies")), Dependencies, OuterOwner);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("containerHealthCheckPort")), ContainerHealthCheckPort);
		UBeamJsonUtils::DeserializeArray<UCliServiceComponentStreamData*>(Bag->GetArrayField(TEXT("components")), Components, OuterOwner);	
	}
};


