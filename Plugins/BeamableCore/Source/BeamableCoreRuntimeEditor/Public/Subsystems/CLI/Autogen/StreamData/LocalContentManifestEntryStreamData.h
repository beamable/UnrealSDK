
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "LocalContentManifestEntryStreamData.generated.h"


UCLASS()
class ULocalContentManifestEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString FullId = {};
	UPROPERTY()
	FString TypeName = {};
	UPROPERTY()
	FString Name = {};
	UPROPERTY()
	int32 CurrentStatus = {};
	UPROPERTY()
	FString Hash = {};
	UPROPERTY()
	TArray<FString> Tags = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FullId"), FullId);
		Serializer->WriteValue(TEXT("TypeName"), TypeName);
		Serializer->WriteValue(TEXT("Name"), Name);
		Serializer->WriteValue(TEXT("CurrentStatus"), CurrentStatus);
		Serializer->WriteValue(TEXT("Hash"), Hash);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FullId"), FullId);
		Serializer->WriteValue(TEXT("TypeName"), TypeName);
		Serializer->WriteValue(TEXT("Name"), Name);
		Serializer->WriteValue(TEXT("CurrentStatus"), CurrentStatus);
		Serializer->WriteValue(TEXT("Hash"), Hash);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Tags"), Tags, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FullId = Bag->GetStringField(TEXT("FullId"));
		TypeName = Bag->GetStringField(TEXT("TypeName"));
		Name = Bag->GetStringField(TEXT("Name"));
		CurrentStatus = Bag->GetIntegerField(TEXT("CurrentStatus"));
		Hash = Bag->GetStringField(TEXT("Hash"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Tags")), Tags, OuterOwner);	
	}
};


