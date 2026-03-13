
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/ContentHistoryChangelistContentEntryStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ContentHistoryContentPageStreamData.generated.h"


UCLASS(BlueprintType)
class UContentHistoryContentPageStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UContentHistoryChangelistContentEntryStreamData*> ContentEntries = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UContentHistoryChangelistContentEntryStreamData*>(TEXT("ContentEntries"), ContentEntries, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UContentHistoryChangelistContentEntryStreamData*>(TEXT("ContentEntries"), ContentEntries, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UContentHistoryChangelistContentEntryStreamData*>(TEXT("ContentEntries"), Bag, ContentEntries, OuterOwner);	
	}
};


