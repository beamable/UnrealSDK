
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
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("OwnerCid"), Bag, OwnerCid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("OwnerPid"), Bag, OwnerPid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ManifestId"), Bag, ManifestId);
		UBeamJsonUtils::DeserializeArray<ULocalContentManifestEntryStreamData*>(TEXT("Entries"), Bag, Entries, OuterOwner);	
	}
};


