#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliVersionCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliVersionStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	FString version = {};
	UPROPERTY()
	FString location = {};
	UPROPERTY()
	FString type = {};
	UPROPERTY()
	FString templates = {};	
};


/**
 Description:
  Commands for managing the CLI version

Usage:
  Beamable.Tools version [command] [options]

Options:
  --show-version                   Displays the executing CLI version [default: True]
  --show-location                  Displays the executing CLI install location [default: True]
  --show-templates                 Displays available Beamable template version [default: True]
  --show-type                      Displays the executing CLI install type [default: True]
  --output <output>                How to display the information, anything other than log will print straight to console with no labels [default: log]
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
  list, ls           Show the most recent available versions
  install <version>  Install a different version of the CLI [default: latest]


 */
UCLASS()
class UBeamCliVersionCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliVersionStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliVersionStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
