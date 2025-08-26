
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DeveloperUserDataStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "DeveloperUserResultStreamData.generated.h"


UCLASS(BlueprintType)
class UDeveloperUserResultStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserDataStreamData*> CreatedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserDataStreamData*> DeletedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserDataStreamData*> UpdatedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserDataStreamData*> SavedUsers = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("CreatedUsers"), CreatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("DeletedUsers"), DeletedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("UpdatedUsers"), UpdatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("SavedUsers"), SavedUsers, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("CreatedUsers"), CreatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("DeletedUsers"), DeletedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("UpdatedUsers"), UpdatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserDataStreamData*>(TEXT("SavedUsers"), SavedUsers, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UDeveloperUserDataStreamData*>(TEXT("CreatedUsers"), Bag, CreatedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserDataStreamData*>(TEXT("DeletedUsers"), Bag, DeletedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserDataStreamData*>(TEXT("UpdatedUsers"), Bag, UpdatedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserDataStreamData*>(TEXT("SavedUsers"), Bag, SavedUsers, OuterOwner);	
	}
};


