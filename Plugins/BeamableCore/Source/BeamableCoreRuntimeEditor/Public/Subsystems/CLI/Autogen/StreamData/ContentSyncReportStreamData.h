
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ContentSyncReportStreamData.generated.h"


UCLASS(BlueprintType)
class UContentSyncReportStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ConflictingContents = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AutoSynchedContents = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ReferenceUpdatedContents = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DeletedCreatedContents = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ConflictingContents"), ConflictingContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("AutoSynchedContents"), AutoSynchedContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ReferenceUpdatedContents"), ReferenceUpdatedContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("DeletedCreatedContents"), DeletedCreatedContents, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ManifestId"), ManifestId, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ConflictingContents"), ConflictingContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("AutoSynchedContents"), AutoSynchedContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ReferenceUpdatedContents"), ReferenceUpdatedContents, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("DeletedCreatedContents"), DeletedCreatedContents, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ManifestId")), ManifestId);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ConflictingContents")), ConflictingContents, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("AutoSynchedContents")), AutoSynchedContents, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ReferenceUpdatedContents")), ReferenceUpdatedContents, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("DeletedCreatedContents")), DeletedCreatedContents, OuterOwner);	
	}
};


