
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServerDescriptorStreamData.generated.h"


UCLASS(BlueprintType)
class UServerDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Port = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 InflightRequests = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Url = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Owner = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("port"), Port, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("inflightRequests"), InflightRequests, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("owner"), Owner, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("port"), Port, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("inflightRequests"), InflightRequests, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("owner"), Owner, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("port"), Bag, Port);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("pid"), Bag, Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("inflightRequests"), Bag, InflightRequests);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("url"), Bag, Url);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("owner"), Bag, Owner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("version"), Bag, Version);	
	}
};


