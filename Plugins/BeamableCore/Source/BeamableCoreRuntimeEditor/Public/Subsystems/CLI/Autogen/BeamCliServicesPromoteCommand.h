#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ManifestChecksumStreamData.h"
#include "BeamCliServicesPromoteCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliServicesPromoteStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UManifestChecksumStreamData*> Manifests = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UManifestChecksumStreamData*>(TEXT("manifests"), Manifests, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UManifestChecksumStreamData*>(TEXT("manifests"), Manifests, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UManifestChecksumStreamData*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);	
	}
};


/**
 Description:
  Promotes the manifest from the given 'sourcePid' to your current realm

Usage:
  Beamable.Tools services promote [options]

Options:
  --source-pid <source-pid>        The PID for the realm from which you wish to pull the manifest from. 
                                   The current realm you are signed into will be updated to match the manifest in the given realm
  --dryrun                         Should any networking happen?
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
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
class UBeamCliServicesPromoteCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesPromoteStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesPromoteStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
