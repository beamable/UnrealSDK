
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/FederationInstanceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "RemoteServiceDescriptorStreamData.generated.h"


UCLASS(BlueprintType)
class URemoteServiceDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 StartedByAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Groups = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UFederationInstanceStreamData*> Federations = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("routingKey"), RoutingKey);
		Serializer->WriteValue(TEXT("startedByAccountId"), StartedByAccountId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);
		UBeamJsonUtils::SerializeArray<UFederationInstanceStreamData*>(TEXT("federations"), Federations, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		RoutingKey = Bag->GetStringField(TEXT("routingKey"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startedByAccountId")), StartedByAccountId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("groups")), Groups, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UFederationInstanceStreamData*>(Bag->GetArrayField(TEXT("federations")), Federations, OuterOwner);	
	}
};


