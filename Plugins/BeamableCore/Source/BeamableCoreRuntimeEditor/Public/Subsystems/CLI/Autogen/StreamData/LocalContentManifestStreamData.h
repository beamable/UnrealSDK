
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "LocalContentManifestStreamData.generated.h"


UCLASS(BlueprintType)
class ULocalContentManifestStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OwnerCid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OwnerPid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ULocalContentManifestEntryStreamData*> Entries = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OwnerCid"), OwnerCid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OwnerPid"), OwnerPid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeArray<ULocalContentManifestEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OwnerCid"), OwnerCid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OwnerPid"), OwnerPid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeArray<ULocalContentManifestEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("OwnerCid")), OwnerCid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("OwnerPid")), OwnerPid);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ManifestId")), ManifestId);
		UBeamJsonUtils::DeserializeArray<ULocalContentManifestEntryStreamData*>(Bag->GetArrayField(TEXT("Entries")), Entries, OuterOwner);	
	}
};


