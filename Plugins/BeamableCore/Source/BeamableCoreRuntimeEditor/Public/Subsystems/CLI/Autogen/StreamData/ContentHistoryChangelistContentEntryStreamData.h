
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryChangelistContentEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryChangelistContentEntryStreamData : public UObject, public IBeamJsonSerializableUObject
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
	int32 ChangeStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NewHash = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OldHash = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> NewTags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> OldTags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> TagsStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString JsonFilePath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReferenceManifestUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ChangeDate = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeStatus"), ChangeStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewHash"), NewHash, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldHash"), OldHash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("NewTags"), NewTags, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("OldTags"), OldTags, Serializer);
		UBeamJsonUtils::SerializeArray<int32>(TEXT("TagsStatus"), TagsStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeDate"), ChangeDate, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeStatus"), ChangeStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewHash"), NewHash, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldHash"), OldHash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("NewTags"), NewTags, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("OldTags"), OldTags, Serializer);
		UBeamJsonUtils::SerializeArray<int32>(TEXT("TagsStatus"), TagsStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeDate"), ChangeDate, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FullId"), Bag, FullId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("TypeName"), Bag, TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Name"), Bag, Name);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ChangeStatus"), Bag, ChangeStatus);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("NewHash"), Bag, NewHash);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("OldHash"), Bag, OldHash);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("NewTags"), Bag, NewTags, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("OldTags"), Bag, OldTags, OuterOwner);
		UBeamJsonUtils::DeserializeArray<int32>(TEXT("TagsStatus"), Bag, TagsStatus, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("JsonFilePath"), Bag, JsonFilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ReferenceManifestUid"), Bag, ReferenceManifestUid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ChangeDate"), Bag, ChangeDate);	
	}
};


