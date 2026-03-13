
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ContentHistoryEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryEntriesPageStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryEntriesPageStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ContainedManifestUids = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 StartDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 EndDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UContentHistoryEntryStreamData*> Entries = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainedManifestUids"), ContainedManifestUids, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("StartDate"), StartDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EndDate"), EndDate, Serializer);
		UBeamJsonUtils::SerializeArray<UContentHistoryEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainedManifestUids"), ContainedManifestUids, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("StartDate"), StartDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("EndDate"), EndDate, Serializer);
		UBeamJsonUtils::SerializeArray<UContentHistoryEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("ContainedManifestUids"), Bag, ContainedManifestUids, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("StartDate"), Bag, StartDate);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("EndDate"), Bag, EndDate);
		UBeamJsonUtils::DeserializeArray<UContentHistoryEntryStreamData*>(TEXT("Entries"), Bag, Entries, OuterOwner);	
	}
};


