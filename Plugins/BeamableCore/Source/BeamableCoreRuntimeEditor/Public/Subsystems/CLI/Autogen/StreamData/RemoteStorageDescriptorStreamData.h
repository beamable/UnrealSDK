
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "RemoteStorageDescriptorStreamData.generated.h"


UCLASS(BlueprintType)
class URemoteStorageDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Storage = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Groups = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storage"), Storage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("storage"), Storage, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("groups"), Groups, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storage"), Bag, Storage);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("groups"), Bag, Groups, OuterOwner);	
	}
};


