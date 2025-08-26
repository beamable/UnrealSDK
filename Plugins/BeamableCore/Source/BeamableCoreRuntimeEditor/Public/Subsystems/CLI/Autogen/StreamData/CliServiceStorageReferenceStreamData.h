
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CliServiceStorageReferenceStreamData.generated.h"


UCLASS(BlueprintType)
class UCliServiceStorageReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StorageType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Enabled = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TemplateId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Checksum = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageType"), StorageType, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("enabled"), Enabled, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("templateId"), TemplateId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageType"), Bag, StorageType);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enabled"), Bag, Enabled);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("templateId"), Bag, TemplateId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);	
	}
};


