
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "OptionalArrayOfServiceDependencyReferenceStreamData.generated.h"


UCLASS()
class UOptionalArrayOfServiceDependencyReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UServiceDependencyReferenceStreamData*> Value = {};
	UPROPERTY()
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceDependencyReferenceStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceDependencyReferenceStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UServiceDependencyReferenceStreamData*>(Bag->GetArrayField(TEXT("Value")), Value, OuterOwner);
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


