
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
	FString Hash = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tags = {};
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
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Hash"), Hash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("FullId"), FullId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("TypeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CurrentStatus"), CurrentStatus, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Hash"), Hash, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("JsonFilePath"), JsonFilePath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ReferenceManifestUid"), ReferenceManifestUid, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("FullId")), FullId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("TypeName")), TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Name")), Name);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("CurrentStatus")), CurrentStatus);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Hash")), Hash);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Tags")), Tags, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("JsonFilePath")), JsonFilePath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ReferenceManifestUid")), ReferenceManifestUid);	
	}
};


