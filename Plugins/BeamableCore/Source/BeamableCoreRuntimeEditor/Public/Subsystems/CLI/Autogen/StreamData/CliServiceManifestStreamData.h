
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
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeArray<UCliServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
		Serializer->WriteValue(TEXT("comments"), Comments);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("created"), Created);
		UBeamJsonUtils::SerializeArray<UCliServiceReferenceStreamData*>(TEXT("manifest"), Manifest, Serializer);
		UBeamJsonUtils::SerializeArray<UCliServiceStorageReferenceStreamData*>(TEXT("storageReference"), StorageReference, Serializer);
		Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
		Serializer->WriteValue(TEXT("comments"), Comments);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
		UBeamJsonUtils::DeserializeArray<UCliServiceReferenceStreamData*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UCliServiceStorageReferenceStreamData*>(Bag->GetArrayField(TEXT("storageReference")), StorageReference, OuterOwner);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdByAccountId")), CreatedByAccountId);
		Comments = Bag->GetStringField(TEXT("comments"));	
	}
};


