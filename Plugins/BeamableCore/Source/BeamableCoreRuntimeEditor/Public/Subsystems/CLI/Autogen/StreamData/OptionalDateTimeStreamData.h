
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "OptionalDateTimeStreamData.generated.h"


UCLASS(BlueprintType)
class UOptionalDateTimeStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime Value = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Value"), Value, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("HasValue"), HasValue, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Value"), Value, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("HasValue"), HasValue, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Value"), Bag, Value);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("HasValue"), Bag, HasValue);	
	}
};


