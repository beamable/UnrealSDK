
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
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("service"), Bag, Service);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceType"), Bag, ServiceType);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("containerId"), Bag, ContainerId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("healthPort"), Bag, HealthPort);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("dataPort"), Bag, DataPort);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("routingKey"), Bag, RoutingKey);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startedByAccountId"), Bag, StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("groups"), Bag, Groups, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Bag, Federations, OuterOwner);	
	}
};


