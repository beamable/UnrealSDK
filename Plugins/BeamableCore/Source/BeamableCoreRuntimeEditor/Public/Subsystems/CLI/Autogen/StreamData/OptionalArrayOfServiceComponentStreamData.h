
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "OptionalArrayOfServiceComponentStreamData.generated.h"


UCLASS()
class UOptionalArrayOfServiceComponentStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UServiceComponentStreamData*> Value = {};
	UPROPERTY()
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceComponentStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceComponentStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UServiceComponentStreamData*>(Bag->GetArrayField(TEXT("Value")), Value, OuterOwner);
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


