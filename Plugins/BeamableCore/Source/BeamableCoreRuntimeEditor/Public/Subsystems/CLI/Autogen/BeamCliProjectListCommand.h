#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliProjectListCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliProjectListStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

		
};


/**
 Description:
  Get a list of microservices

Usage:
  Beamable.Tools project list [options]

Options:
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
class UBeamCliProjectListCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliProjectListStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliProjectListStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
