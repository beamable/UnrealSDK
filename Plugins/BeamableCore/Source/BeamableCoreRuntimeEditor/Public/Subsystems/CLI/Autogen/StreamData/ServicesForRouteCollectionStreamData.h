
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DockerServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/FederationInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/HostServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RemoteServiceDescriptorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServicesForRouteCollectionStreamData.generated.h"


UCLASS(BlueprintType)
class UServicesForRouteCollectionStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool KnownToBeRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UServiceInstanceStreamData*> Instances = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UFederationInstanceStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("knownToBeRunning"), KnownToBeRunning, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceInstanceStreamData*>(TEXT("instances"), Instances, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("knownToBeRunning"), KnownToBeRunning, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceInstanceStreamData*>(TEXT("instances"), Instances, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("knownToBeRunning")), KnownToBeRunning);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("routingKey")), RoutingKey);
		UBeamJsonUtils::DeserializeArray<UServiceInstanceStreamData*>(Bag->GetArrayField(TEXT("instances")), Instances, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationInstanceStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


