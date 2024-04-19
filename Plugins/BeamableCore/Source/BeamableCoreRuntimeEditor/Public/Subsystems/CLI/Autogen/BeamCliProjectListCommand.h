#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceInfoStreamData.h"
#include "BeamCliProjectListCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectListStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UServiceInfoStreamData*> LocalServices = {};
	UPROPERTY()
	TArray<UServiceInfoStreamData*> LocalStorages = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceInfoStreamData*>(TEXT("localServices"), LocalServices, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceInfoStreamData*>(TEXT("localStorages"), LocalStorages, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UServiceInfoStreamData*>(TEXT("localServices"), LocalServices, Serializer);
		UBeamJsonUtils::SerializeArray<UServiceInfoStreamData*>(TEXT("localStorages"), LocalStorages, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UServiceInfoStreamData*>(Bag->GetArrayField(TEXT("localServices")), LocalServices, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UServiceInfoStreamData*>(Bag->GetArrayField(TEXT("localStorages")), LocalStorages, OuterOwner);	
	}
};


/**
 Description:
  Get a list of microservices

Usage:
  Beamable.Tools project list [options]

Options:
  --dryrun                         Should any networking happen?
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
  -q, --quiet                      When true, skip input waiting and use defaults [default: False]
  --host <host>                    The host endpoint for beamable
  --refresh-token <refresh-token>  Refresh token to use for the requests
  --log, --logs <log>              Extra logs gets printed out
  --dir <dir>                      Directory to use for configuration
  --raw                            Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                         Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>      a custom location for dotnet
  -?, -h, --help                   Show help and usage information



 */
UCLASS()
class UBeamCliProjectListCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectListStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectListStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
