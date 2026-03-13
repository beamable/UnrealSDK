
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ProcessInfoStreamData.generated.h"


UCLASS(BlueprintType)
class UProcessInfoStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProcessId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CommandLine = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> LockingFiles = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ProcessId"), ProcessId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CommandLine"), CommandLine, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LockingFiles"), LockingFiles, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("ProcessId"), ProcessId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("CommandLine"), CommandLine, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LockingFiles"), LockingFiles, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ProcessId"), Bag, ProcessId);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CommandLine"), Bag, CommandLine);
		UBeamJsonUtils::DeserializeArray<FString>(TEXT("LockingFiles"), Bag, LockingFiles, OuterOwner);	
	}
};


