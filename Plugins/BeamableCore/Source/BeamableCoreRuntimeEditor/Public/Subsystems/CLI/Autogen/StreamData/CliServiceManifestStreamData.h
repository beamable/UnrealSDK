
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/CliServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceDependencyStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceStorageReferenceStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "CliServiceManifestStreamData.generated.h"


UCLASS(BlueprintType)
class UCliServiceManifestStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCliServiceReferenceStreamData*> Manifest = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UCliServiceStorageReferenceStreamData*> StorageReference = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedByAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Comments = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdByAccountId"), CreatedByAccountId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("comments"), Comments, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdByAccountId"), CreatedByAccountId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("comments"), Comments, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
		UBeamJsonUtils::DeserializeArray<UCliServiceReferenceStreamData*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UCliServiceStorageReferenceStreamData*>(Bag->GetArrayField(TEXT("storageReference")), StorageReference, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("createdByAccountId")), CreatedByAccountId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("comments")), Comments);	
	}
};


