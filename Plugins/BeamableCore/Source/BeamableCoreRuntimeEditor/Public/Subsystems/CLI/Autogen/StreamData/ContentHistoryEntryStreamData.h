
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PublishedBy = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PublishedByName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AffectedContentIds = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestUid"), ManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedBy"), PublishedBy, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedByName"), PublishedByName, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("AffectedContentIds"), AffectedContentIds, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestUid"), ManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CreatedDate"), CreatedDate, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedBy"), PublishedBy, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PublishedByName"), PublishedByName, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("AffectedContentIds"), AffectedContentIds, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ManifestUid"), Bag, ManifestUid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CreatedDate"), Bag, CreatedDate);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PublishedBy"), Bag, PublishedBy);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PublishedByName"), Bag, PublishedByName);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("AffectedContentIds"), Bag, AffectedContentIds, OuterOwner);	
	}
};


