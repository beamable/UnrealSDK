
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "OptionalStringStreamData.generated.h"


UCLASS()
class UOptionalStringStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Value = {};
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
		Value = Bag->GetStringField(TEXT("Value"));
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


