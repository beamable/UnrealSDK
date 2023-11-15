#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliServicesSetLocalManifestCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Set the entire state of the local manifest, overwriting any existing entries

Usage:
  Beamable.Tools services set-local-manifest [options]

Options:
  --local-http-names <local-http-names>                Local http service names
  --local-http-contexts <local-http-contexts>          Local http service docker build contexts
  --local-http-docker-files <local-http-docker-files>  Local http service relative docker file paths
  --dryrun                                             Should any networking happen?
  --cid <cid>                                          Cid to use; will default to whatever is in the file system
  --pid <pid>                                          Pid to use; will default to whatever is in the file system
  --host <host>                                        The host endpoint for beamable
  --refresh-token <refresh-token>                      Refresh token to use for the requests
  --log <log>                                          Extra logs gets printed out
  --dir <dir>                                          Directory to use for configuration
  --dotnet-path <dotnet-path>                          a custom location for dotnet
  -?, -h, --help                                       Show help and usage information



 */
UCLASS()
class UBeamCliServicesSetLocalManifestCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
