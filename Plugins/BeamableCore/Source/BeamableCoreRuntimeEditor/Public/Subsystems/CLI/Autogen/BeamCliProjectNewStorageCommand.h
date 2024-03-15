#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectNewStorageCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Create and add a new Microstorage

Usage:
  Beamable.Tools project new-storage <name> [options]

Arguments:
  <name>  The name of the new Microstorage.

Options:
  --sln <sln>                      The path to the solution that the Microstorage will be added to
  --output-path <output-path>      The path where the storage is going to be created, a new sln is going to be created as well
  --link-to <link-to>              The name of the project to link this storage to
  -q, --quiet                      When true, skip input waiting and use defaults [default: False]
  --dryrun                         Should any networking happen?
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
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
class UBeamCliProjectNewStorageCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
