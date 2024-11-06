
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageStatusStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "OptionalArrayOfServiceStorageStatusStreamData.generated.h"


UCLASS()
class UOptionalArrayOfServiceStorageStatusStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UServiceStorageStatusStreamData*> Value = {};
	UPROPERTY()
	bool HasValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceStorageStatusStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceStorageStatusStreamData*>(TEXT("Value"), Value, Serializer);
		Serializer->WriteValue(TEXT("HasValue"), HasValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UServiceStorageStatusStreamData*>(Bag->GetArrayField(TEXT("Value")), Value, OuterOwner);
		HasValue = Bag->GetBoolField(TEXT("HasValue"));	
	}
};


