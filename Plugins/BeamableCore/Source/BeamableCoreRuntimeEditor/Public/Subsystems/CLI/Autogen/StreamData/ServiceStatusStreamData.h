
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServicesForRouteCollectionStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DockerServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/HostServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RemoteServiceDescriptorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceStatusStreamData.generated.h"


UCLASS()
class UServiceStatusStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	FString ServiceType = {};
	UPROPERTY()
	TArray<FString> Groups = {};
	UPROPERTY()
	TArray<UServicesForRouteCollectionStreamData*> AvailableRoutes = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UServicesForRouteCollectionStreamData*>(TEXT("availableRoutes"), AvailableRoutes, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UServicesForRouteCollectionStreamData*>(TEXT("availableRoutes"), AvailableRoutes, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		ServiceType = Bag->GetStringField(TEXT("serviceType"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServicesForRouteCollectionStreamData*>(Bag->GetArrayField(TEXT("availableRoutes")), AvailableRoutes, OuterOwner);	
	}
};

