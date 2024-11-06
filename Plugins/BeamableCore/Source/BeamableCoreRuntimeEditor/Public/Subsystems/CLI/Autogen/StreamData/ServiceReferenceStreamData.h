
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalLongStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceReferenceStreamData.generated.h"


UCLASS()
class UServiceReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool Archived = {};
	UPROPERTY()
	bool Arm = {};
	UPROPERTY()
	FString Checksum = {};
	UPROPERTY()
	UOptionalStringStreamData* Comments = {};
	UPROPERTY()
	UOptionalArrayOfServiceComponentStreamData* Components = {};
	UPROPERTY()
	UOptionalLongStreamData* ContainerHealthCheckPort = {};
	UPROPERTY()
	UOptionalArrayOfServiceDependencyReferenceStreamData* Dependencies = {};
	UPROPERTY()
	bool Enabled = {};
	UPROPERTY()
	UOptionalStringStreamData* ImageCpuArch = {};
	UPROPERTY()
	FString ImageId = {};
	UPROPERTY()
	FString ServiceName = {};
	UPROPERTY()
	FString TemplateId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("archived"), Archived);
		Serializer->WriteValue(TEXT("arm"), Arm);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("comments", Comments, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceComponentStreamData*>("components", Components, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalLongStreamData*>("containerHealthCheckPort", ContainerHealthCheckPort, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceDependencyReferenceStreamData*>("dependencies", Dependencies, Serializer);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("imageCpuArch", ImageCpuArch, Serializer);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("archived"), Archived);
		Serializer->WriteValue(TEXT("arm"), Arm);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("comments", Comments, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceComponentStreamData*>("components", Components, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalLongStreamData*>("containerHealthCheckPort", ContainerHealthCheckPort, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceDependencyReferenceStreamData*>("dependencies", Dependencies, Serializer);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("imageCpuArch", ImageCpuArch, Serializer);
		Serializer->WriteValue(TEXT("imageId"), ImageId);
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Archived = Bag->GetBoolField(TEXT("archived"));
		Arm = Bag->GetBoolField(TEXT("arm"));
		Checksum = Bag->GetStringField(TEXT("checksum"));
		UBeamJsonUtils::DeserializeUObject<UOptionalStringStreamData*>("comments", Bag, Comments, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UOptionalArrayOfServiceComponentStreamData*>("components", Bag, Components, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UOptionalLongStreamData*>("containerHealthCheckPort", Bag, ContainerHealthCheckPort, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UOptionalArrayOfServiceDependencyReferenceStreamData*>("dependencies", Bag, Dependencies, OuterOwner);
		Enabled = Bag->GetBoolField(TEXT("enabled"));
		UBeamJsonUtils::DeserializeUObject<UOptionalStringStreamData*>("imageCpuArch", Bag, ImageCpuArch, OuterOwner);
		ImageId = Bag->GetStringField(TEXT("imageId"));
		ServiceName = Bag->GetStringField(TEXT("serviceName"));
		TemplateId = Bag->GetStringField(TEXT("templateId"));	
	}
};


