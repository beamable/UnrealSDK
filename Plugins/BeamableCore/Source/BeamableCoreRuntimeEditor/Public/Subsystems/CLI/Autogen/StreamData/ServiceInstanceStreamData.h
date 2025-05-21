
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DockerServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/FederationInstanceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/HostServiceDescriptorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RemoteServiceDescriptorStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceInstanceStreamData.generated.h"


UCLASS(BlueprintType)
class UServiceInstanceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 StartedByAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StartedByAccountEmail = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PrimaryKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDockerServiceDescriptorStreamData* LatestDockerEvent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHostServiceDescriptorStreamData* LatestHostEvent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URemoteServiceDescriptorStreamData* LatestRemoteEvent = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountId"), StartedByAccountId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountEmail"), StartedByAccountEmail, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("primaryKey"), PrimaryKey, Serializer);
		UBeamJsonUtils::SerializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", LatestDockerEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", LatestHostEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", LatestRemoteEvent, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountId"), StartedByAccountId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedByAccountEmail"), StartedByAccountEmail, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("primaryKey"), PrimaryKey, Serializer);
		UBeamJsonUtils::SerializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", LatestDockerEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", LatestHostEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", LatestRemoteEvent, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startedByAccountEmail")), StartedByAccountEmail);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("primaryKey")), PrimaryKey);
		UBeamJsonUtils::DeserializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", Bag, LatestDockerEvent, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", Bag, LatestHostEvent, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", Bag, LatestRemoteEvent, OuterOwner);	
	}
};


