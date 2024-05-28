#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectNewCommonLibCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Create common library project that later can be connected to the services

Usage:
  Beamable.Tools project new common-lib <name> [options]

Arguments:
  <name>  The name of the new library project

Options:
  -i, --init                       Automatically create a .beamable folder context if no context exists
  --sln <sln>                      Relative path to the .sln file to use for the new project. If the .sln file does not exist, it will be created. By default, when no value is provided, the .sln path will be <name>/<name>.sln []
  --version <version>              Specifies version of Beamable project dependencies. Defaults to the current version of the CLI [default: 0.0.123]
  --output-path <output-path>      The path where the project is going to be created
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
class UBeamCliProjectNewCommonLibCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
