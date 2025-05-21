
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "SettingOutputStreamData.generated.h"


UCLASS(BlueprintType)
class USettingOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("key")), Key);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);	
	}
};


