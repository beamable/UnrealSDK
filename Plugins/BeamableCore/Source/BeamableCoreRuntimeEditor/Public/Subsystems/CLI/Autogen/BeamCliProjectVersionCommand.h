#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectVersionCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliProjectVersionStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ProjectPaths = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> PackageNames = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> PackageVersions = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("projectPaths"), ProjectPaths, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageNames"), PackageNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageVersions"), PackageVersions, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("projectPaths"), ProjectPaths, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageNames"), PackageNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageVersions"), PackageVersions, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("projectPaths")), ProjectPaths, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("packageNames")), PackageNames, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("packageVersions")), PackageVersions, OuterOwner);	
	}
};


/**
 Description:
  Commands that lists Beamable package versions of a SAMS projects

Usage:
  Beamable.Tools project version [options]

Options:
  --requested-version <requested-version>  Request specific version of Beamable packages
  --dryrun                                 Should any networking happen?
  --cid <cid>                              Cid to use; will default to whatever is in the file system
  --pid <pid>                              Pid to use; will default to whatever is in the file system
  -q, --quiet                              When true, skip input waiting and use defaults [default: False]
  --host <host>                            The host endpoint for beamable
  --access-token <access-token>            The access token to use for the requests
  --refresh-token <refresh-token>          Refresh token to use for the requests
  --log, --logs <log>                      Extra logs gets printed out
  --no-redirect                            If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                            By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                            By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>      a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                           Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                       Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>    additional file paths to be included when building a local project manifest.
  --dir <dir>                              Directory to use for configuration
  --raw                                    Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                 Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>              a custom location for dotnet [default: dotnet]
  -?, -h, --help                           Show help and usage information



 */
UCLASS()
class UBeamCliProjectVersionCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectVersionStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectVersionStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
