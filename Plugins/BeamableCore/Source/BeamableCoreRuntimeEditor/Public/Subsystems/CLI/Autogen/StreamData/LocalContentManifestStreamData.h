
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "LocalContentManifestStreamData.generated.h"


UCLASS()
class ULocalContentManifestStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ManifestId = {};
	UPROPERTY()
	TArray<ULocalContentManifestEntryStreamData*> Entries = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("ManifestId"), ManifestId);
		UBeamJsonUtils::SerializeArray<ULocalContentManifestEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("ManifestId"), ManifestId);
		UBeamJsonUtils::SerializeArray<ULocalContentManifestEntryStreamData*>(TEXT("Entries"), Entries, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ManifestId = Bag->GetStringField(TEXT("ManifestId"));
		UBeamJsonUtils::DeserializeArray<ULocalContentManifestEntryStreamData*>(Bag->GetArrayField(TEXT("Entries")), Entries, OuterOwner);	
	}
};


