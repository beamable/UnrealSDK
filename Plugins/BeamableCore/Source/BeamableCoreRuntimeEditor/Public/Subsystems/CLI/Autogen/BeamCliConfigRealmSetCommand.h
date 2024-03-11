#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliConfigRealmSetCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliConfigRealmSetStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TMap<FString, FString> Config = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeMap<FString>(TEXT("Config"), Config, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeMap<FString>(TEXT("Config"), Config, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("Config")), Config, OuterOwner);	
	}
};


/**
 Description:
  Set realm config values

Usage:
  Beamable.Tools config realm set [options]

Options:
  --key-values <key-values>        A list of realm config key/value pairs in a 'namespace|key::value' format
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
class UBeamCliConfigRealmSetCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliConfigRealmSetStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliConfigRealmSetStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
