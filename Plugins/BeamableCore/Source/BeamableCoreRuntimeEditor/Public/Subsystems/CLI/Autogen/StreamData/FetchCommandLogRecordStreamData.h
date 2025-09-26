
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "FetchCommandLogRecordStreamData.generated.h"


UCLASS(BlueprintType)
class UFetchCommandLogRecordStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Timestamp = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LogLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Timestamp"), Timestamp, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LogLevel"), LogLevel, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ServiceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Message"), Message, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Timestamp"), Timestamp, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LogLevel"), LogLevel, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ServiceName"), ServiceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Message"), Message, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Timestamp"), Bag, Timestamp);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("LogLevel"), Bag, LogLevel);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ServiceName"), Bag, ServiceName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Message"), Bag, Message);	
	}
};


