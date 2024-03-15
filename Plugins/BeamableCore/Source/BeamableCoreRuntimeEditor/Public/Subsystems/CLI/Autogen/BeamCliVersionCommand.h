#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliVersionCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliVersionStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Version = {};
	UPROPERTY()
	FString Location = {};
	UPROPERTY()
	FString Type = {};
	UPROPERTY()
	FString Templates = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("version"), Version);
		Serializer->WriteValue(TEXT("location"), Location);
		Serializer->WriteValue(TEXT("type"), Type);
		Serializer->WriteValue(TEXT("templates"), Templates);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("version"), Version);
		Serializer->WriteValue(TEXT("location"), Location);
		Serializer->WriteValue(TEXT("type"), Type);
		Serializer->WriteValue(TEXT("templates"), Templates);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Version = Bag->GetStringField(TEXT("version"));
		Location = Bag->GetStringField(TEXT("location"));
		Type = Bag->GetStringField(TEXT("type"));
		Templates = Bag->GetStringField(TEXT("templates"));	
	}
};


/**
 Description:
  Commands for managing the CLI version

Usage:
  Beamable.Tools version [command] [options]

Options:
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

Commands:
  construct <major> <minor> <patch>  [INTERNAL] constructs a beamable version string with the given configuration
  list, ls                           Show the most recent available versions
  install <version>                  Install a different version of the CLI [default: latest]


 */
UCLASS()
class UBeamCliVersionCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliVersionStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliVersionStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
