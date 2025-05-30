
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
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("FullId")), FullId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("TypeName")), TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Name")), Name);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CurrentStatus")), CurrentStatus);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("IsInConflict")), IsInConflict);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Hash")), Hash);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Tags")), Tags, OuterOwner);
		UBeamJsonUtils::DeserializeArray<int32>(Bag->GetArrayField(TEXT("TagsStatus")), TagsStatus, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("JsonFilePath")), JsonFilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ReferenceManifestUid")), ReferenceManifestUid);	
	}
};


