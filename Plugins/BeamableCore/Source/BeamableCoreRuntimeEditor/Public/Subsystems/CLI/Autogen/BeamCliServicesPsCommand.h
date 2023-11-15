#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliServicesPsCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliServicesPsStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

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
  --host <host>                    The host endpoint for beamable
  --refresh-token <refresh-token>  Refresh token to use for the requests
  --log <log>                      Extra logs gets printed out
  --dir <dir>                      Directory to use for configuration
  --dotnet-path <dotnet-path>      a custom location for dotnet
  -?, -h, --help                   Show help and usage information



 */
UCLASS()
class UBeamCliServicesPsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliServicesPsStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliServicesPsStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
