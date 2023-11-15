#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliInitCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliInitStreamData
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
  Initialize a new Beamable project in the current directory

Usage:
  Beamable.Tools init [options]

Options:
  --username <username>            Specify user name
  --password <password>            User password
  --host <host>                    The host endpoint for beamable
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
  --refresh-token <refresh-token>  Refresh token to use for the requests
  --save-to-environment            Save login refresh token to environment variable
  --save-to-file                   Save login refresh token to file
  --customer-scoped                Make request customer scoped instead of product only
  --print-to-console               Prints out login request response to console
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
class UBeamCliInitCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliInitStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliInitStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
