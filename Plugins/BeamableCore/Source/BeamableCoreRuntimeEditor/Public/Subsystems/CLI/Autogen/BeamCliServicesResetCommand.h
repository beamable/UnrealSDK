#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliServicesResetCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliServicesResetStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	FString Target = {};
	UPROPERTY()
	TArray<FString> Ids = {};	
};


/**
 Description:
  Resets services to default settings and cleans up docker images (if any exist)

Usage:
  Beamable.Tools services reset <target> [options]

Arguments:
  <target>  Either image|container|protocols.'image' will cleanup all your locally built images for the selected Beamo Services.
            'container' will stop all your locally running containers for the selected Beamo Services.
            'protocols' will reset all the protocol data for the selected Beamo Services back to default parameters

Options:
  --ids <ids>                      The ids for the services you wish to reset
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
class UBeamCliServicesResetCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliServicesResetStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliServicesResetStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
