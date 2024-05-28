#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliConfigCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliConfigStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Host = {};
	UPROPERTY()
	FString Cid = {};
	UPROPERTY()
	FString Pid = {};
	UPROPERTY()
	FString ConfigPath = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("host"), Host);
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("configPath"), ConfigPath);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("host"), Host);
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("configPath"), ConfigPath);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Host = Bag->GetStringField(TEXT("host"));
		Cid = Bag->GetStringField(TEXT("cid"));
		Pid = Bag->GetStringField(TEXT("pid"));
		ConfigPath = Bag->GetStringField(TEXT("configPath"));	
	}
};


/**
 Description:
  List the current beamable configuration

Usage:
  Beamable.Tools config [command] [options]

Options:
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

Commands:
  secret              Get the realm secret
  set <name> <value>  Set a config value
  realm               Get current realm config values


 */
UCLASS()
class UBeamCliConfigCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliConfigStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliConfigStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
