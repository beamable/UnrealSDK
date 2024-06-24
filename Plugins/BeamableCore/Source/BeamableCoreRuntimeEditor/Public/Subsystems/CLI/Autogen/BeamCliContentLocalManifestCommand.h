#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/LocalContentManifestEntryStreamData.h"
#include "BeamCliContentLocalManifestCommand.generated.h"


UCLASS()
class UBeamCliContentLocalManifestStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<ULocalContentManifestStreamData*> Manifests = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<ULocalContentManifestStreamData*>(TEXT("Manifests"), Manifests, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<ULocalContentManifestStreamData*>(TEXT("Manifests"), Manifests, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<ULocalContentManifestStreamData*>(Bag->GetArrayField(TEXT("Manifests")), Manifests, OuterOwner);	
	}
};


/**
 Description:
  [INTERNAL] Gets the current local manifest

Usage:
  Beamable.Tools content local-manifest [options]

Options:
  --manifest-ids <manifest-ids>    Inform a subset of ','-separated manifest ids for which to return data. By default, will return all manifests []
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
class UBeamCliContentLocalManifestCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliContentLocalManifestStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliContentLocalManifestStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
