
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ContentHistoryChangelistEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryChangelistStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryChangelistStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PreviousManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PublishedBy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 PublishedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UContentHistoryChangelistEntryStreamData*> Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UContentHistoryChangelistEntryStreamData*> Removed = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UContentHistoryChangelistEntryStreamData*> Modified = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestUid"), ManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PreviousManifestUid"), PreviousManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedBy"), PublishedBy, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedAt"), PublishedAt, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Created"), Created, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Removed"), Removed, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Modified"), Modified, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestUid"), ManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PreviousManifestUid"), PreviousManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedBy"), PublishedBy, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedAt"), PublishedAt, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Created"), Created, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Removed"), Removed, Serializer);
		UBeamJsonUtils::SerializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Modified"), Modified, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ManifestUid"), Bag, ManifestUid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PreviousManifestUid"), Bag, PreviousManifestUid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PublishedBy"), Bag, PublishedBy);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PublishedAt"), Bag, PublishedAt);
		UBeamJsonUtils::DeserializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Created"), Bag, Created, OuterOwner);
		UBeamJsonUtils::DeserializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Removed"), Bag, Removed, OuterOwner);
		UBeamJsonUtils::DeserializeMap<UContentHistoryChangelistEntryStreamData*>(TEXT("Modified"), Bag, Modified, OuterOwner);	
	}
};


