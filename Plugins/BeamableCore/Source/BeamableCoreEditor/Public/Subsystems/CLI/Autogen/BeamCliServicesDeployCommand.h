#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliServicesDeployCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliServicesDeployStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	bool Success;
	UPROPERTY()
	FString FailureReason;	
};


USTRUCT()
struct FBeamCliServicesDeployLocalProgressStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("local_progress"));

	UPROPERTY()
	FString BeamoId;
	UPROPERTY()
	double LocalDeployProgress;	
};


USTRUCT()
struct FBeamCliServicesDeployRemoteProgressStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("remote_progress"));

	UPROPERTY()
	FString BeamoId;
	UPROPERTY()
	double BuildAndTestProgress;
	UPROPERTY()
	double ContainerUploadProgress;	
};


/**
 Description:
  Deploys services, either locally or remotely (to the current realm)

Usage:
  Beamable.Tools services deploy [options]

Options:
  --ids <ids>                            The ids for the services you wish to deploy. Ignoring this option deploys all services.If '--remote' option is set, these are the ids that'll become enabled by Beam-O once it receives the updated manifest
  --remote                               If this option is set, we publish the manifest instead [default: False]
  --from-file <from-file>                If this option is set to a valid path to a ServiceManifest JSON, deploys that instead. Only works if --remote flag is set []
  --comment <comment>                    Requires --remote flag. Associates this comment along with the published Manifest. You'll be able to read it via the Beamable Portal []
  --service-comments <service-comments>  Requires --remote flag. Any number of 'BeamoId::Comment' strings. 
                                         Associates each comment to the given Beamo Id if it's among the published services. You'll be able to read it via the Beamable Portal []
  --dryrun                               Should any networking happen?
  --cid <cid>                            Cid to use; will default to whatever is in the file system
  --pid <pid>                            Pid to use; will default to whatever is in the file system
  --host <host>                          The host endpoint for beamable
  --refresh-token <refresh-token>        Refresh token to use for the requests
  --log <log>                            Extra logs gets printed out
  --dir <dir>                            Directory to use for configuration
  -?, -h, --help                         Show help and usage information



 */
UCLASS()
class UBeamCliServicesDeployCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliServicesDeployStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliServicesDeployStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	TArray<FBeamCliServicesDeployLocalProgressStreamData> LocalProgressStream;
	TArray<int64> LocalProgressTimestamps;
	TFunction<void (const TArray<FBeamCliServicesDeployLocalProgressStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnLocalProgressStreamOutput;

	TArray<FBeamCliServicesDeployRemoteProgressStreamData> RemoteProgressStream;
	TArray<int64> RemoteProgressTimestamps;
	TFunction<void (const TArray<FBeamCliServicesDeployRemoteProgressStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnRemoteProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
