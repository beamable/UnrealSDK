#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectNewCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Start a brand new beamable solution using dotnet

Usage:
  Beamable.Tools project new <name> [<output>] [options]

Arguments:
  <name>    Name of the new project
  <output>  Where the project be created []

Options:
  --skip-common                    If you should create a common library
  --solution-name <solution-name>  The name of the solution of the new project
  --version <version>              Specifies version of Beamable project dependencies []
  --disable                        Create service that is disabled on publish
  -q, --quiet                      When true, automatically accept path suggestions [default: False]
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
class UBeamCliProjectNewCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
