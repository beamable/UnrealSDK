
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DockerServiceDescriptorStreamData.generated.h"


UCLASS()
class UDockerServiceDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	FString ServiceType = {};
	UPROPERTY()
	FString ContainerId = {};
	UPROPERTY()
	int32 HealthPort = {};
	UPROPERTY()
	int32 DataPort = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	int64 StartedByAccountId = {};
	UPROPERTY()
	TArray<FString> Groups = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		Serializer->WriteValue(TEXT("containerId"), ContainerId);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("dataPort"), DataPort);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		Serializer->WriteValue(TEXT("containerId"), ContainerId);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("dataPort"), DataPort);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		ServiceType = Bag->GetStringField(TEXT("serviceType"));
		ContainerId = Bag->GetStringField(TEXT("containerId"));
		HealthPort = Bag->GetIntegerField(TEXT("healthPort"));
		DataPort = Bag->GetIntegerField(TEXT("dataPort"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);	
	}
};

