#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliProjectOpenSwaggerCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Opens the swagger page for a given service

Usage:
  Beamable.Tools project open-swagger [<service-name>] [options]

Arguments:
  <service-name>  Name of the service to open swagger to []

Options:
  --remote                         If passed, swagger will open to the remote version of this service. Otherwise, it will try and use the local version
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
class UBeamCliProjectOpenSwaggerCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
