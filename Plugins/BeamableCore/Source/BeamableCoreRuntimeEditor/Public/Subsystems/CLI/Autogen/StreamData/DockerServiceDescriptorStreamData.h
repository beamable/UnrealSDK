
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/FederationInstanceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "DockerServiceDescriptorStreamData.generated.h"


UCLASS(BlueprintType)
class UDockerServiceDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ContainerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthPort = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DataPort = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 StartedByAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Groups = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UFederationInstanceStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceType"), ServiceType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("containerId"), ContainerId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("healthPort"), HealthPort, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("dataPort"), DataPort, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountId"), StartedByAccountId, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceType"), ServiceType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("containerId"), ContainerId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("healthPort"), HealthPort, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("dataPort"), DataPort, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountId"), StartedByAccountId, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceType")), ServiceType);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("containerId")), ContainerId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("healthPort")), HealthPort);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dataPort")), DataPort);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("routingKey")), RoutingKey);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationInstanceStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


