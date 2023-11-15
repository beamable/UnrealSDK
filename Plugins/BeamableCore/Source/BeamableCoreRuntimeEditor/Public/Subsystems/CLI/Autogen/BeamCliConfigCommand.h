#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliConfigCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliConfigStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	FString host = {};
	UPROPERTY()
	FString cid = {};
	UPROPERTY()
	FString pid = {};	
};


/**
 Description:
  List the current beamable configuration

Usage:
  Beamable.Tools config [command] [options]

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

Commands:
  set <name> <value>  Set a config value
  secret              Get the realm secret


 */
UCLASS()
class UBeamCliConfigCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliConfigStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliConfigStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
