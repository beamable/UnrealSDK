
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
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("checksum"), Checksum);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("templateId"), TemplateId);
		Serializer->WriteValue(TEXT("checksum"), Checksum);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		StorageType = Bag->GetStringField(TEXT("storageType"));
		Enabled = Bag->GetBoolField(TEXT("enabled"));
		TemplateId = Bag->GetStringField(TEXT("templateId"));
		Checksum = Bag->GetStringField(TEXT("checksum"));	
	}
};


