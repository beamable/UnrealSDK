
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "HostServiceDescriptorStreamData.generated.h"


UCLASS()
class UHostServiceDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	int32 ProcessId = {};
	UPROPERTY()
	int32 HealthPort = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	int64 StartedByAccountId = {};
	UPROPERTY()
	TArray<FString> Groups = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("processId"), ProcessId);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("processId"), ProcessId);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		ProcessId = Bag->GetIntegerField(TEXT("processId"));
		HealthPort = Bag->GetIntegerField(TEXT("healthPort"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);	
	}
};


