
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ContentHistoryChangelistStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ContentHistoryChangelistEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryChangelistPageStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryChangelistPageStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UContentHistoryChangelistStreamData*> Changelists = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UContentHistoryChangelistStreamData*>(TEXT("Changelists"), Changelists, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UContentHistoryChangelistStreamData*>(TEXT("Changelists"), Changelists, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UContentHistoryChangelistStreamData*>(TEXT("Changelists"), Bag, Changelists, OuterOwner);	
	}
};


