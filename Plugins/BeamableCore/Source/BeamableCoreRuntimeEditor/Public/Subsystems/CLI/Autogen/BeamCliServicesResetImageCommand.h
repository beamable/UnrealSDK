#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesResetImageCommand.generated.h"


UCLASS()
class UBeamCliServicesResetImageStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Id = {};
	UPROPERTY()
	FString Message = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("message"), Message);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("message"), Message);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		Message = Bag->GetStringField(TEXT("message"));	
	}
};


/**
 Description:
  Delete any images associated with the given Beamable services

Usage:
  Beamable.Tools services reset image [options]

Options:
  --ids <ids>                          The list of services to include, defaults to all local services (separated by whitespace)
  --dryrun                             Should any networking happen?
  --cid <cid>                          Cid to use; will default to whatever is in the file system
  --pid <pid>                          Pid to use; will default to whatever is in the file system
  -q, --quiet                          When true, skip input waiting and use defaults [default: False]
  --host <host>                        The host endpoint for beamable
  --access-token <access-token>        The access token to use for the requests
  --refresh-token <refresh-token>      Refresh token to use for the requests
  --log, --logs <log>                  Extra logs gets printed out
  --no-redirect                        If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                        By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                        By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>  a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                       Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                   Out all log messages as data payloads in addition to however they are logged
  --dir <dir>                          Directory to use for configuration
  --raw                                Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                             Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>          a custom location for dotnet [default: dotnet]
  -?, -h, --help                       Show help and usage information



 */
UCLASS()
class UBeamCliServicesResetImageCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesResetImageStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesResetImageStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
