
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryChangelistEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryChangelistEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OldVersion = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString OldChecksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> OldTags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NewVersion = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NewChecksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> NewTags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString JsonFilePath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FullId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TypeName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ChangeStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ChangeDate = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldVersion"), OldVersion, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldChecksum"), OldChecksum, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("OldTags"), OldTags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewVersion"), NewVersion, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewChecksum"), NewChecksum, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("NewTags"), NewTags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeStatus"), ChangeStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeDate"), ChangeDate, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldVersion"), OldVersion, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("OldChecksum"), OldChecksum, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("OldTags"), OldTags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewVersion"), NewVersion, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("NewChecksum"), NewChecksum, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("NewTags"), NewTags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeStatus"), ChangeStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ChangeDate"), ChangeDate, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("OldVersion"), Bag, OldVersion);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("OldChecksum"), Bag, OldChecksum);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("OldTags"), Bag, OldTags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("NewVersion"), Bag, NewVersion);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("NewChecksum"), Bag, NewChecksum);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("NewTags"), Bag, NewTags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("JsonFilePath"), Bag, JsonFilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("FullId"), Bag, FullId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("TypeName"), Bag, TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Name"), Bag, Name);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ChangeStatus"), Bag, ChangeStatus);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ChangeDate"), Bag, ChangeDate);	
	}
};


