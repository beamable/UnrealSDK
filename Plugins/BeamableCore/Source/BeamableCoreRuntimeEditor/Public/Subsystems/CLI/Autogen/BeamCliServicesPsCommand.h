#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesPsCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliServicesPsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> ExistInLocal = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> ExistInRemote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> IsRunningRemotely = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDockerRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> BeamoIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> ShouldBeEnabledOnRemote = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<bool> IsRunningLocally = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ProtocolTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ImageIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ContainerNames = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ContainerIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> LocalHostPorts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> LocalContainerPorts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Dependencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ProjectPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> UnityAssemblyDefinitions = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInLocal"), ExistInLocal, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInRemote"), ExistInRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("IsRunningRemotely"), IsRunningRemotely, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsDockerRunning"), IsDockerRunning, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("BeamoIds"), BeamoIds, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ShouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("IsRunningLocally"), IsRunningLocally, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProtocolTypes"), ProtocolTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ImageIds"), ImageIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerNames"), ContainerNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerIds"), ContainerIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalHostPorts"), LocalHostPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalContainerPorts"), LocalContainerPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProjectPath"), ProjectPath, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("UnityAssemblyDefinitions"), UnityAssemblyDefinitions, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInLocal"), ExistInLocal, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInRemote"), ExistInRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("IsRunningRemotely"), IsRunningRemotely, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("IsDockerRunning"), IsDockerRunning, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("BeamoIds"), BeamoIds, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ShouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("IsRunningLocally"), IsRunningLocally, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProtocolTypes"), ProtocolTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ImageIds"), ImageIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerNames"), ContainerNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerIds"), ContainerIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalHostPorts"), LocalHostPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalContainerPorts"), LocalContainerPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProjectPath"), ProjectPath, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("UnityAssemblyDefinitions"), UnityAssemblyDefinitions, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("ExistInLocal")), ExistInLocal, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("ExistInRemote")), ExistInRemote, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("IsRunningRemotely")), IsRunningRemotely, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("IsDockerRunning")), IsDockerRunning);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("BeamoIds")), BeamoIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("ShouldBeEnabledOnRemote")), ShouldBeEnabledOnRemote, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("IsRunningLocally")), IsRunningLocally, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ProtocolTypes")), ProtocolTypes, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ImageIds")), ImageIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ContainerNames")), ContainerNames, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ContainerIds")), ContainerIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("LocalHostPorts")), LocalHostPorts, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("LocalContainerPorts")), LocalContainerPorts, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Dependencies")), Dependencies, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ProjectPath")), ProjectPath, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("UnityAssemblyDefinitions")), UnityAssemblyDefinitions, OuterOwner);	
	}
};


/**
 Description:
  Lists the current local or remote service manifest and status (as summary table or json)

Usage:
  Beamable.Tools services ps [options]

Options:
  --json                                 Outputs as json instead of summary table
  --dryrun                               [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                            CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --pid <pid>                            PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                            When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                          This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>          The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>        A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                    Extra logs gets printed out
  --no-redirect                          If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation       By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                          By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                          By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>    a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                         Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                     Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>  additional file paths to be included when building a local project manifest.
  --dir <dir>                            [DEPRECATED] Path override for the .beamable folder
  --raw                                  Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                               Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>            a custom location for dotnet [default: dotnet]
  -?, -h, --help                         Show help and usage information



 */
UCLASS()
class UBeamCliServicesPsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesPsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (TArray<UBeamCliServicesPsStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
