
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
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		Serializer->WriteValue(TEXT("startedByAccountEmail"), StartedByAccountEmail);
		Serializer->WriteValue(TEXT("primaryKey"), PrimaryKey);
		UBeamJsonUtils::SerializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", LatestDockerEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", LatestHostEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", LatestRemoteEvent, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		Serializer->WriteValue(TEXT("startedByAccountEmail"), StartedByAccountEmail);
		Serializer->WriteValue(TEXT("primaryKey"), PrimaryKey);
		UBeamJsonUtils::SerializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", LatestDockerEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", LatestHostEvent, Serializer);
		UBeamJsonUtils::SerializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", LatestRemoteEvent, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		StartedByAccountEmail = Bag->GetStringField(TEXT("startedByAccountEmail"));
		PrimaryKey = Bag->GetStringField(TEXT("primaryKey"));
		UBeamJsonUtils::DeserializeUObject<UDockerServiceDescriptorStreamData*>("latestDockerEvent", Bag, LatestDockerEvent, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UHostServiceDescriptorStreamData*>("latestHostEvent", Bag, LatestHostEvent, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<URemoteServiceDescriptorStreamData*>("latestRemoteEvent", Bag, LatestRemoteEvent, OuterOwner);	
	}
};


