
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DockerServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/FederationInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/HostServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RemoteServiceDescriptorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServicesForRouteCollectionStreamData.generated.h"


UCLASS()
class UServicesForRouteCollectionStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool KnownToBeRunning = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	TArray<UServiceInstanceStreamData*> Instances = {};
	UPROPERTY()
	TArray<UFederationInstanceStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("knownToBeRunning"), KnownToBeRunning);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		UBeamJsonUtils::SerializeArray<UServiceInstanceStreamData*>(TEXT("instances"), Instances, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("knownToBeRunning"), KnownToBeRunning);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		UBeamJsonUtils::SerializeArray<UServiceInstanceStreamData*>(TEXT("instances"), Instances, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		KnownToBeRunning = Bag->GetBoolField(TEXT("knownToBeRunning"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		UBeamJsonUtils::DeserializeArray<UServiceInstanceStreamData*>(Bag->GetArrayField(TEXT("instances")), Instances, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationInstanceStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


