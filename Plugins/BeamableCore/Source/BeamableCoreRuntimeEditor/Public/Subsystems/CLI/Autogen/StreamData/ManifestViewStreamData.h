
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalLongStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageReferenceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ManifestViewStreamData.generated.h"


UCLASS()
class UManifestViewStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Checksum = {};
	UPROPERTY()
	UOptionalStringStreamData* Comments = {};
	UPROPERTY()
	int64 Created = {};
	UPROPERTY()
	UOptionalLongStreamData* CreatedByAccountId = {};
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	TArray<UServiceReferenceStreamData*> Manifest = {};
	UPROPERTY()
	UOptionalArrayOfServiceStorageReferenceStreamData* StorageReference = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("comments", Comments, Serializer);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeUObject<UOptionalLongStreamData*>("createdByAccountId", CreatedByAccountId, Serializer);
		Serializer->WriteValue(TEXT("id"), Id);
		UBeamJsonUtils::SerializeArray<UServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceStorageReferenceStreamData*>("storageReference", StorageReference, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		UBeamJsonUtils::SerializeUObject<UOptionalStringStreamData*>("comments", Comments, Serializer);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeUObject<UOptionalLongStreamData*>("createdByAccountId", CreatedByAccountId, Serializer);
		Serializer->WriteValue(TEXT("id"), Id);
		UBeamJsonUtils::SerializeArray<UServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeUObject<UOptionalArrayOfServiceStorageReferenceStreamData*>("storageReference", StorageReference, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Checksum = Bag->GetStringField(TEXT("checksum"));
		UBeamJsonUtils::DeserializeUObject<UOptionalStringStreamData*>("comments", Bag, Comments, OuterOwner);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
		UBeamJsonUtils::DeserializeUObject<UOptionalLongStreamData*>("createdByAccountId", Bag, CreatedByAccountId, OuterOwner);
		Id = Bag->GetStringField(TEXT("id"));
		UBeamJsonUtils::DeserializeArray<UServiceReferenceStreamData*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UOptionalArrayOfServiceStorageReferenceStreamData*>("storageReference", Bag, StorageReference, OuterOwner);	
	}
};


