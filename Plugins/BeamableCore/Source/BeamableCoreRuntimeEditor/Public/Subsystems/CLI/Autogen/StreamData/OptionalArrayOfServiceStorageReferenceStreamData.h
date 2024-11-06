
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "OptionalArrayOfServiceStorageReferenceStreamData.generated.h"


UCLASS()
class UOptionalArrayOfServiceStorageReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UServiceStorageReferenceStreamData*> Value = {};
	UPROPERTY()
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceStorageReferenceStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceStorageReferenceStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UServiceStorageReferenceStreamData*>(Bag->GetArrayField(TEXT("Value")), Value, OuterOwner);
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


