
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CollectorStatusStreamData.generated.h"


UCLASS(BlueprintType)
class UCollectorStatusStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReady = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OtlpEndpoint = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRunning"), IsRunning, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isReady"), IsReady, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("otlpEndpoint"), OtlpEndpoint, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRunning"), IsRunning, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("isReady"), IsReady, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("otlpEndpoint"), OtlpEndpoint, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isRunning"), Bag, IsRunning);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isReady"), Bag, IsReady);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("pid"), Bag, Pid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("otlpEndpoint"), Bag, OtlpEndpoint);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("version"), Bag, Version);	
	}
};


