
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DeveloperUserStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "DeveloperUserResultStreamData.generated.h"


UCLASS(BlueprintType)
class UDeveloperUserResultStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserStreamData*> CreatedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserStreamData*> DeletedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserStreamData*> UpdatedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserStreamData*> SavedUsers = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDeveloperUserStreamData*> CorruptedUsers = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("CreatedUsers"), CreatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("DeletedUsers"), DeletedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("UpdatedUsers"), UpdatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("SavedUsers"), SavedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("CorruptedUsers"), CorruptedUsers, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("CreatedUsers"), CreatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("DeletedUsers"), DeletedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("UpdatedUsers"), UpdatedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("SavedUsers"), SavedUsers, Serializer);
		UBeamJsonUtils::SerializeArray<UDeveloperUserStreamData*>(TEXT("CorruptedUsers"), CorruptedUsers, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UDeveloperUserStreamData*>(Bag->GetArrayField(TEXT("CreatedUsers")), CreatedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserStreamData*>(Bag->GetArrayField(TEXT("DeletedUsers")), DeletedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserStreamData*>(Bag->GetArrayField(TEXT("UpdatedUsers")), UpdatedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserStreamData*>(Bag->GetArrayField(TEXT("SavedUsers")), SavedUsers, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UDeveloperUserStreamData*>(Bag->GetArrayField(TEXT("CorruptedUsers")), CorruptedUsers, OuterOwner);	
	}
};


