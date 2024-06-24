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
	bool IsLocal = {};
	UPROPERTY()
	bool IsDockerRunning = {};
	UPROPERTY()
	TArray<FString> BeamoIds = {};
	UPROPERTY()
	TArray<bool> ShouldBeEnabledOnRemote = {};
	UPROPERTY()
	TArray<bool> RunningState = {};
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

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("IsLocal"), IsLocal);
		Serializer->WriteValue(TEXT("IsDockerRunning"), IsDockerRunning);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("BeamoIds"), BeamoIds, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ShouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("RunningState"), RunningState, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProtocolTypes"), ProtocolTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ImageIds"), ImageIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerNames"), ContainerNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerIds"), ContainerIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalHostPorts"), LocalHostPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalContainerPorts"), LocalContainerPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProjectPath"), ProjectPath, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("IsLocal"), IsLocal);
		Serializer->WriteValue(TEXT("IsDockerRunning"), IsDockerRunning);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("BeamoIds"), BeamoIds, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("ShouldBeEnabledOnRemote"), ShouldBeEnabledOnRemote, Serializer);
		UBeamJsonUtils::SerializeArray<bool>(TEXT("RunningState"), RunningState, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProtocolTypes"), ProtocolTypes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ImageIds"), ImageIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerNames"), ContainerNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ContainerIds"), ContainerIds, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalHostPorts"), LocalHostPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("LocalContainerPorts"), LocalContainerPorts, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Dependencies"), Dependencies, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("ProjectPath"), ProjectPath, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		IsLocal = Bag->GetBoolField(TEXT("IsLocal"));
		IsDockerRunning = Bag->GetBoolField(TEXT("IsDockerRunning"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("BeamoIds")), BeamoIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("ShouldBeEnabledOnRemote")), ShouldBeEnabledOnRemote, OuterOwner);
		UBeamJsonUtils::DeserializeArray<bool>(Bag->GetArrayField(TEXT("RunningState")), RunningState, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ProtocolTypes")), ProtocolTypes, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ImageIds")), ImageIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ContainerNames")), ContainerNames, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ContainerIds")), ContainerIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("LocalHostPorts")), LocalHostPorts, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("LocalContainerPorts")), LocalContainerPorts, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Dependencies")), Dependencies, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("ProjectPath")), ProjectPath, OuterOwner);	
	}
};


/**
 Description:
  Lists the current local or remote service manifest and status (as summary table or json)

Usage:
  Beamable.Tools services ps [options]

Options:
  --remote                         Makes it so that we output the current realm's remote manifest, instead of the local one
  --json                           Outputs as json instead of summary table
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
