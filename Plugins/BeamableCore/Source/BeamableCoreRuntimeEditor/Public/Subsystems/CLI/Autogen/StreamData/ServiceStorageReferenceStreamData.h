
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceStorageReferenceStreamData.generated.h"


UCLASS()
class UServiceStorageReferenceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool Archived = {};
	UPROPERTY()
	FString Checksum = {};
	UPROPERTY()
	bool Enabled = {};
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	FString StorageType = {};
	UPROPERTY()
	UOptionalStringStreamData* TemplateId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("archived"), Archived);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("templateId", TemplateId, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("archived"), Archived);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("enabled"), Enabled);
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("storageType"), StorageType);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("templateId", TemplateId, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Archived = Bag->GetBoolField(TEXT("archived"));
		Checksum = Bag->GetStringField(TEXT("checksum"));
		Enabled = Bag->GetBoolField(TEXT("enabled"));
		Id = Bag->GetStringField(TEXT("id"));
		StorageType = Bag->GetStringField(TEXT("storageType"));
		UBeamJsonUtils::DeserializeUObject<UOptionalStringStreamData*>("templateId", Bag, TemplateId, OuterOwner);	
	}
};


