
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceStorageReferenceStreamData.generated.h"


UCLASS()
class UServiceStorageReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	FString StorageType = {};
	UPROPERTY()
	bool Enabled = {};
	UPROPERTY()
	FString TemplateId = {};
	UPROPERTY()
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


