
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ManifestProjectDataStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ManifestAuthorStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ContentSnapshotListItemStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ManifestSnapshotItemStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestSnapshotItemStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UManifestProjectDataStreamData* ProjectData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 SavedTimestamp = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UManifestAuthorStreamData* Author = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAutoSnapshot = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UContentSnapshotListItemStreamData*> Contents = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Path"), Path, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeUObject<UManifestProjectDataStreamData*>("ProjectData", ProjectData, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("SavedTimestamp"), SavedTimestamp, Serializer);
		UBeamJsonUtils::SerializeUObject<UManifestAuthorStreamData*>("Author", Author, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsAutoSnapshot"), IsAutoSnapshot, Serializer);
		UBeamJsonUtils::SerializeArray<UContentSnapshotListItemStreamData*>(TEXT("Contents"), Contents, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Path"), Path, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeUObject<UManifestProjectDataStreamData*>("ProjectData", ProjectData, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("SavedTimestamp"), SavedTimestamp, Serializer);
		UBeamJsonUtils::SerializeUObject<UManifestAuthorStreamData*>("Author", Author, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsAutoSnapshot"), IsAutoSnapshot, Serializer);
		UBeamJsonUtils::SerializeArray<UContentSnapshotListItemStreamData*>(TEXT("Contents"), Contents, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Name"), Bag, Name);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Path"), Bag, Path);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ManifestId"), Bag, ManifestId);
		UBeamJsonUtils::DeserializeUObject<UManifestProjectDataStreamData*>("ProjectData", Bag, ProjectData, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("SavedTimestamp"), Bag, SavedTimestamp);
		UBeamJsonUtils::DeserializeUObject<UManifestAuthorStreamData*>("Author", Bag, Author, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("IsAutoSnapshot"), Bag, IsAutoSnapshot);
		UBeamJsonUtils::DeserializeArray<UContentSnapshotListItemStreamData*>(TEXT("Contents"), Bag, Contents, OuterOwner);	
	}
};


