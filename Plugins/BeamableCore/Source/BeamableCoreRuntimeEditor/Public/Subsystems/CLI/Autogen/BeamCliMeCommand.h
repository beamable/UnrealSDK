#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "BeamCliMeCommand.generated.h"

class FMonitoredProcess;


USTRUCT()
struct FBeamCliMeStreamData
{
	GENERATED_BODY()

	inline static FString StreamTypeName = FString(TEXT("stream"));

	UPROPERTY()
	int64 id = {};
	UPROPERTY()
	FString email = {};
	UPROPERTY()
	FString language = {};
	UPROPERTY()
	TArray<FString> scopes = {};
	UPROPERTY()
	TArray<FString> thirdPartyAppAssociations = {};
	UPROPERTY()
	TArray<FString> deviceIds = {};	
};


/**
 Description:
  Temp command to get current account

Usage:
  Beamable.Tools me [options]

Options:
  --plain-output                   Make command returns plain text without custom colors and formatting
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
class UBeamCliMeCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	TArray<FBeamCliMeStreamData> Stream;
	TArray<int64> Timestamps;
	TFunction<void (const TArray<FBeamCliMeStreamData>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
