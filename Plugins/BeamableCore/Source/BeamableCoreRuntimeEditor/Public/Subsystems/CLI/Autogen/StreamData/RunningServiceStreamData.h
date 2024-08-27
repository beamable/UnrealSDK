
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
	FString Name = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	FString FullName = {};
	UPROPERTY()
	int32 InstanceCount = {};
	UPROPERTY()
	bool TrafficFilterEnabled = {};
	UPROPERTY()
	int64 AuthorPlayerId = {};
	UPROPERTY()
	TArray<URunningFederationStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("fullName"), FullName);
		Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
		Serializer->WriteValue(TEXT("trafficFilterEnabled"), TrafficFilterEnabled);
		Serializer->WriteValue(TEXT("authorPlayerId"), AuthorPlayerId);
		UBeamJsonUtils::SerializeArray<URunningFederationStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("fullName"), FullName);
		Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
		Serializer->WriteValue(TEXT("trafficFilterEnabled"), TrafficFilterEnabled);
		Serializer->WriteValue(TEXT("authorPlayerId"), AuthorPlayerId);
		UBeamJsonUtils::SerializeArray<URunningFederationStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FullName = Bag->GetStringField(TEXT("fullName"));
		InstanceCount = Bag->GetIntegerField(TEXT("instanceCount"));
		TrafficFilterEnabled = Bag->GetBoolField(TEXT("trafficFilterEnabled"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("authorPlayerId")), AuthorPlayerId);
		UBeamJsonUtils::DeserializeArray<URunningFederationStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


