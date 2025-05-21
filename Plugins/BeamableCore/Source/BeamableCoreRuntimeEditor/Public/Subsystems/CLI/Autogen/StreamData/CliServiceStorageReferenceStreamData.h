
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
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageType")), StorageType);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("enabled")), Enabled);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("templateId")), TemplateId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);	
	}
};


