
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CliServiceDependencyStreamData.generated.h"


UCLASS()
class UCliServiceDependencyStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString StorageType = {};
	UPROPERTY()
	FString Id = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		Serializer->WriteValue(TEXT("id"), Id);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		Serializer->WriteValue(TEXT("id"), Id);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		StorageType = Bag->GetStringField(TEXT("storageType"));
		Id = Bag->GetStringField(TEXT("id"));	
	}
};


