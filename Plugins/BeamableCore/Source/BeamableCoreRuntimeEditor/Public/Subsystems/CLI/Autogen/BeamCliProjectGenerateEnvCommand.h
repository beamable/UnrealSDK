#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/EnvVarOutputStreamData.h"
#include "BeamCliProjectGenerateEnvCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectGenerateEnvStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UEnvVarOutputStreamData*> EnvVars = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UEnvVarOutputStreamData*>(TEXT("envVars"), EnvVars, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UEnvVarOutputStreamData*>(TEXT("envVars"), EnvVars, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UEnvVarOutputStreamData*>(Bag->GetArrayField(TEXT("envVars")), EnvVars, OuterOwner);	
	}
};


/**
 Description:
  [INTERNAL] Get the connection strings required to start a Microservice. This is used when running Standalone Microservices locally without Docker

Usage:
  Beamable.Tools project generate-env <service> <output> [options]

Arguments:
  <service>  Which service to generate the .env file for
  <output>   Where to output the .env file

Options:
  --include-prefix                   If true, the generated .env file will include the local machine name as prefix [default: True]
  --instance-count <instance-count>  How many virtual websocket connections the server will open [default: 1]
  --auto-deploy                      When enabled, automatically deploy dependencies that aren't running [default: False]
  --dryrun                           Should any networking happen?
  --cid <cid>                        Cid to use; will default to whatever is in the file system
  --pid <pid>                        Pid to use; will default to whatever is in the file system
  -q, --quiet                        When true, skip input waiting and use defaults [default: False]
  --host <host>                      The host endpoint for beamable
  --refresh-token <refresh-token>    Refresh token to use for the requests
  --log, --logs <log>                Extra logs gets printed out
  --dir <dir>                        Directory to use for configuration
  --raw                              Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                           Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>        a custom location for dotnet
  -?, -h, --help                     Show help and usage information




 */
UCLASS()
class UBeamCliProjectGenerateEnvCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectGenerateEnvStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectGenerateEnvStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
