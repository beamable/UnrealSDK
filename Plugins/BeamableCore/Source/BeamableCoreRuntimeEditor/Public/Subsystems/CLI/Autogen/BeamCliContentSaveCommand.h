#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliContentSaveCommand.generated.h"

class FMonitoredProcess;



/**
 Description:
  Saves a serialized content properties JSON-blob into a manifest

Usage:
  Beamable.Tools content save [options]

Options:
  --manifest-ids <manifest-ids>              Inform a subset of ','-separated manifest ids for which to return data. By default, will return all manifests []
  --content-ids <content-ids>                An array of existing content ids []
  --content-properties <content-properties>  An array, parallel to the --content-ids, that contain the escaped properties json for each content []
  --dryrun                                   Should any networking happen?
  --cid <cid>                                Cid to use; will default to whatever is in the file system
  --pid <pid>                                Pid to use; will default to whatever is in the file system
  -q, --quiet                                When true, skip input waiting and use defaults [default: False]
  --host <host>                              The host endpoint for beamable
  --refresh-token <refresh-token>            Refresh token to use for the requests
  --log, --logs <log>                        Extra logs gets printed out
  --dir <dir>                                Directory to use for configuration
  --raw                                      Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                   Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                a custom location for dotnet
  -?, -h, --help                             Show help and usage information



 */
UCLASS()
class UBeamCliContentSaveCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
