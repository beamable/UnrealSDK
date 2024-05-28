#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectGeneratePropertiesCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Generates a Directory.Build.props file with the beam path and solution dir

Usage:
  Beamable.Tools project generate-properties <output> <beam-path> <solution-dir> [options]

Arguments:
  <output>        Where the file will be created
  <beam-path>     Beam path to be used. Use BEAM_SOLUTION_DIR to template in $(SolutionDir)
  <solution-dir>  The solution path to be used. 
                  The following values have special meaning and are not treated as paths... 
                  - "DIR.PROPS" = $([System.IO.Path]::GetDirectoryName(`$(DirectoryBuildPropsPath)`))

Options:
  --build-dir <build-dir>          A path relative to the given solution directory, that will be used to store the projects /bin and /obj directories. Note: the given path will have the project's assembly name and the bin or obj folder appended
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
class UBeamCliProjectGeneratePropertiesCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
