#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceManifestStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceDependencyStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/CliServiceStorageReferenceStreamData.h"
#include "BeamCliServicesManifestsCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliServicesManifestsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UCliServiceManifestStreamData*> Manifests = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UCliServiceManifestStreamData*>(TEXT("manifests"), Manifests, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UCliServiceManifestStreamData*>(TEXT("manifests"), Manifests, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UCliServiceManifestStreamData*>(Bag->GetArrayField(TEXT("manifests")), Manifests, OuterOwner);	
	}
};


/**
 Description:
  Outputs manifests json to console

Usage:
  Beamable.Tools services manifests [options]

Options:
  --limit <limit>                  Limits amount of manifests
  --skip <skip>                    Skip specified amount of manifests
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
class UBeamCliServicesManifestsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesManifestsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesManifestsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
