
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "SetEnabledCommandComponentStreamData.generated.h"


UCLASS(BlueprintType)
class USetEnabledCommandComponentStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Enabled = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("enabled")), Enabled);	
	}
};


