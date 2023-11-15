#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliOapiDownloadCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Download the Beamable Open API specs

Usage:
  Beamable.Tools oapi download [options]

Options:
  --output <output>                When null or empty, the generated code will be sent to standard-out. When there is a output value, the file or files will be written to the path []
  --filter <filter>                Filter which open apis to generate. An empty string matches everything []
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
class UBeamCliOapiDownloadCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
