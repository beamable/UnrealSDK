
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
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageType")), StorageType);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);	
	}
};


