#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliServicesRunCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliServicesRunStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	bool Success = {};
	UPROPERTY()
	FString FailureReason = {};	
};


USTRUCT()
struct FBeamCliServicesRunLocalProgressStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("local_progress"));

	UPROPERTY()
	FString BeamoId = {};
	UPROPERTY()
	double LocalDeployProgress = {};	
};


/**
 Description:
  Run services locally in Docker. Will fail if no docker instance is running in the local machine

Usage:
  Beamable.Tools services run [options]

Options:
  --ids <ids>                      The ids for the services you wish to deploy. Ignoring this option deploys all services
  -fcpu, --force-amd-cpu-arch      Force the services to run with amd64 CPU architecture, useful when deploying from computers with ARM architecture [default: False]
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
class UBeamCliServicesRunCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliServicesRunStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliServicesRunStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	TArray<FBeamCliServicesRunLocalProgressStreamData> LocalProgressStream;
	TArray<int64> LocalProgressTimestamps;
	TFunction<void (const TArray<FBeamCliServicesRunLocalProgressStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnLocalProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
