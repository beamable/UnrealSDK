
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "LocalContentManifestEntryStreamData.generated.h"


UCLASS(BlueprintType)
class ULocalContentManifestEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FullId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TypeName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInConflict = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hash = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> TagsStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString JsonFilePath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReferenceManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 LatestUpdateAtDate = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CurrentStatus"), CurrentStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsInConflict"), IsInConflict, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Hash"), Hash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeArray<int32>(TEXT("TagsStatus"), TagsStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LatestUpdateAtDate"), LatestUpdateAtDate, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CurrentStatus"), CurrentStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsInConflict"), IsInConflict, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Hash"), Hash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeArray<int32>(TEXT("TagsStatus"), TagsStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("LatestUpdateAtDate"), LatestUpdateAtDate, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FullId"), Bag, FullId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("TypeName"), Bag, TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Name"), Bag, Name);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CurrentStatus"), Bag, CurrentStatus);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsInConflict"), Bag, IsInConflict);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Hash"), Bag, Hash);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("Tags"), Bag, Tags, OuterOwner);
		UBeamJsonUtils::DeserializeArray<int32>(TEXT("TagsStatus"), Bag, TagsStatus, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("JsonFilePath"), Bag, JsonFilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ReferenceManifestUid"), Bag, ReferenceManifestUid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("LatestUpdateAtDate"), Bag, LatestUpdateAtDate);	
	}
};


