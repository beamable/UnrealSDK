
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "OptionalLongStreamData.generated.h"


UCLASS()
class UOptionalLongStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	int64 Value = {};
	UPROPERTY()
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Value"), Value);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Value"), Value);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("Value")), Value);
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


