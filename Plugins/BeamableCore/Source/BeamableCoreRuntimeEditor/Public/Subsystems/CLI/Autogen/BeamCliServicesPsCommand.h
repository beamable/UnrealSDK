#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesPsCommand.generated.h"


UCLASS()
class UBeamCliServicesPsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<bool> ExistInLocal = {};
	UPROPERTY()
	TArray<bool> ExistInRemote = {};
	UPROPERTY()
	TArray<bool> IsRunningRemotely = {};
	UPROPERTY()
	bool IsDockerRunning = {};
	UPROPERTY()
	TArray<FString> BeamoIds = {};
	UPROPERTY()
	TArray<bool> ShouldBeEnabledOnRemote = {};
	UPROPERTY()
	TArray<bool> IsRunningLocally = {};
	UPROPERTY()
	TArray<FString> ProtocolTypes = {};
	UPROPERTY()
	TArray<FString> ImageIds = {};
	UPROPERTY()
	TArray<FString> ContainerNames = {};
	UPROPERTY()
	TArray<FString> ContainerIds = {};
	UPROPERTY()
	TArray<FString> LocalHostPorts = {};
	UPROPERTY()
	TArray<FString> LocalContainerPorts = {};
	UPROPERTY()
	TArray<FString> Dependencies = {};
	UPROPERTY()
	TArray<FString> ProjectPath = {};
	UPROPERTY()
	TArray<FString> UnityAssemblyDefinitions = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInLocal"), ExistInLocal, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ExistInRemote"), ExistInRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("IsRunningRemotely"), IsRunningRemotely, Serializer);
		Serializer->WriteValue(TEXT("IsDockerRunning"), IsDockerRunning);
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
		Serializer->WriteValue(TEXT("IsDockerRunning"), IsDockerRunning);
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
		IsDockerRunning = Bag->GetBoolField(TEXT("IsDockerRunning"));
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
  --json                               Outputs as json instead of summary table
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
  --dir <dir>                          Directory to use for configuration
  --raw                                Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                             Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>          a custom location for dotnet [default: dotnet]
  -?, -h, --help                       Show help and usage information



 */
UCLASS()
class UBeamCliServicesPsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesPsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesPsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
