
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CliServiceDependencyStreamData.generated.h"


UCLASS(BlueprintType)
class UCliServiceDependencyStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StorageType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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


