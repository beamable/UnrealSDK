
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "RemoteServiceDescriptorStreamData.generated.h"


UCLASS()
class URemoteServiceDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	FString RoutingKey = {};
	UPROPERTY()
	int64 StartedByAccountId = {};
	UPROPERTY()
	TArray<FString> Groups = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);	
	}
};


