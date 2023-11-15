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
	bool Success = {};
	UPROPERTY()
	FString FailureReason = {};	
};


USTRUCT()
struct FBeamCliServicesDeployRemoteProgressStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("remote_progress"));

	UPROPERTY()
	FString BeamoId = {};
	UPROPERTY()
	double BuildAndTestProgress = {};
	UPROPERTY()
	double ContainerUploadProgress = {};	
};


/**
 Description:
  Deploys services remotely to the current realm

Usage:
  Beamable.Tools services deploy [options]

Options:
  --enable <enable>                            These are the ids for services you wish to be enabled once Beam-O receives the updated manifest
  --disable <disable>                          These are the ids for services you wish to be disabled once Beam-O receives the updated manifest
  --from-file <from-file>                      If this option is set to a valid path to a ServiceManifest JSON, deploys that instead []
  --comment <comment>                          Associates this comment along with the published Manifest. You'll be able to read it via the Beamable Portal []
  --service-comments <service-comments>        Any number of strings in the format BeamoId::Comment
                                               Associates each comment to the given Beamo Id if it's among the published services. You'll be able to read it via the Beamable Portal []
  --docker-registry-url <docker-registry-url>  A custom docker registry url to use when uploading. By default, the result from the beamo/registry network call will be used, with minor string manipulation to add https scheme, remove port specificatino, and add /v2
  --dryrun                                     Should any networking happen?
  --cid <cid>                                  Cid to use; will default to whatever is in the file system
  --pid <pid>                                  Pid to use; will default to whatever is in the file system
  --host <host>                                The host endpoint for beamable
  --refresh-token <refresh-token>              Refresh token to use for the requests
  --log <log>                                  Extra logs gets printed out
  --dir <dir>                                  Directory to use for configuration
  --dotnet-path <dotnet-path>                  a custom location for dotnet
  -?, -h, --help                               Show help and usage information



 */
UCLASS()
class UBeamCliServicesDeployCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliServicesDeployStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliServicesDeployStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	TArray<FBeamCliServicesDeployRemoteProgressStreamData> RemoteProgressStream;
	TArray<int64> RemoteProgressTimestamps;
	TFunction<void (const TArray<FBeamCliServicesDeployRemoteProgressStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnRemoteProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
