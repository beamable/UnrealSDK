
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/RunningFederationStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "RunningServiceStreamData.generated.h"


UCLASS()
class URunningServiceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ServiceName = {};
	UPROPERTY()
	FString BeamoName = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	FString FullName = {};
	UPROPERTY()
	int32 InstanceCount = {};
	UPROPERTY()
	bool TrafficFilterEnabled = {};
	UPROPERTY()
	int64 StartedByAccountId = {};
	UPROPERTY()
	TArray<URunningFederationStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("beamoName"), BeamoName);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("fullName"), FullName);
		Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
		Serializer->WriteValue(TEXT("trafficFilterEnabled"), TrafficFilterEnabled);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<URunningFederationStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);
		Serializer->WriteValue(TEXT("beamoName"), BeamoName);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("fullName"), FullName);
		Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
		Serializer->WriteValue(TEXT("trafficFilterEnabled"), TrafficFilterEnabled);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<URunningFederationStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceName = Bag->GetStringField(TEXT("serviceName"));
		BeamoName = Bag->GetStringField(TEXT("beamoName"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FullName = Bag->GetStringField(TEXT("fullName"));
		InstanceCount = Bag->GetIntegerField(TEXT("instanceCount"));
		TrafficFilterEnabled = Bag->GetBoolField(TEXT("trafficFilterEnabled"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<URunningFederationStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


