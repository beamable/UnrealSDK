#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesRegistryCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliServicesRegistryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString RegistryUrl = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("registryUrl"), RegistryUrl);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("registryUrl"), RegistryUrl);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		RegistryUrl = Bag->GetStringField(TEXT("registryUrl"));	
	}
};


/**
 Description:
  Gets the docker registry URL that we upload docker images into when deploying services remotely for this realm

Usage:
  Beamable.Tools services registry [options]

Options:
  --dryrun                         Should any networking happen?
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
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
class UBeamCliServicesRegistryCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesRegistryStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesRegistryStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
