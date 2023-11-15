#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliProjectLogsCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliProjectLogsStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	FString timeStamp = {};
	UPROPERTY()
	FString message = {};
	UPROPERTY()
	FString logLevel = {};
	UPROPERTY()
	FString raw = {};	
};


/**
 Description:
  Tail the logs of a microservice

Usage:
  Beamable.Tools project logs <service> [options]

Arguments:
  <service>  The name of the service to view logs for

Options:
  --reconnect                      If the service stops, and reconnect is enabled, then the logs command will wait for the service to restart and then reattach to logs [default: True]
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
class UBeamCliProjectLogsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliProjectLogsStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliProjectLogsStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
