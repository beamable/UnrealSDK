
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageReferenceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceManifestStreamData.generated.h"


UCLASS()
class UServiceManifestStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	int64 Created = {};
	UPROPERTY()
	TArray<UServiceReferenceStreamData*> Manifest = {};
	UPROPERTY()
	TArray<UServiceStorageReferenceStreamData*> StorageReference = {};
	UPROPERTY()
	int64 CreatedByAccountId = {};
	UPROPERTY()
	FString Comments = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeArray<UServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
		Serializer->WriteValue(TEXT("comments"), Comments);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeArray<UServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
		Serializer->WriteValue(TEXT("comments"), Comments);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
		UBeamJsonUtils::DeserializeArray<UServiceReferenceStreamData*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServiceStorageReferenceStreamData*>(Bag->GetArrayField(TEXT("storageReference")), StorageReference, OuterOwner);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdByAccountId")), CreatedByAccountId);
		Comments = Bag->GetStringField(TEXT("comments"));	
	}
};


