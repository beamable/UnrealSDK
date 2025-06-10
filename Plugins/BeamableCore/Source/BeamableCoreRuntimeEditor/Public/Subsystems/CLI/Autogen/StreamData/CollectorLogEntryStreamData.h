
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CollectorLogEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UCollectorLogEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Level = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime Timestamp = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Level"), Level, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Timestamp"), Timestamp, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Level"), Level, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Timestamp"), Timestamp, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Level")), Level);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Message")), Message);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Timestamp")), Timestamp);	
	}
};


