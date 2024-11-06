
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceStorageStatusStreamData.generated.h"


UCLASS()
class UServiceStorageStatusStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	bool IsCurrent = {};
	UPROPERTY()
	bool IsRunning = {};
	UPROPERTY()
	FString StorageType = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("isCurrent"), IsCurrent);
		Serializer->WriteValue(TEXT("isRunning"), IsRunning);
		Serializer->WriteValue(TEXT("storageType"), StorageType);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("isCurrent"), IsCurrent);
		Serializer->WriteValue(TEXT("isRunning"), IsRunning);
		Serializer->WriteValue(TEXT("storageType"), StorageType);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		IsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
		IsRunning = Bag->GetBoolField(TEXT("isRunning"));
		StorageType = Bag->GetStringField(TEXT("storageType"));	
	}
};


