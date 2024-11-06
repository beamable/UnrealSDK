
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "GetLogsUrlHeaderStreamData.generated.h"


UCLASS(BlueprintType)
class UGetLogsUrlHeaderStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("key"), Key);
		Serializer->WriteValue(TEXT("value"), Value);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("key"), Key);
		Serializer->WriteValue(TEXT("value"), Value);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Key = Bag->GetStringField(TEXT("key"));
		Value = Bag->GetStringField(TEXT("value"));	
	}
};


