#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectLogsCommand.generated.h"


UCLASS()
class UBeamCliProjectLogsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Raw = {};
	UPROPERTY()
	FString LogLevel = {};
	UPROPERTY()
	FString Message = {};
	UPROPERTY()
	FString TimeStamp = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("raw"), Raw);
		Serializer->WriteValue(TEXT("logLevel"), LogLevel);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("timeStamp"), TimeStamp);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("raw"), Raw);
		Serializer->WriteValue(TEXT("logLevel"), LogLevel);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("timeStamp"), TimeStamp);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Raw = Bag->GetStringField(TEXT("raw"));
		LogLevel = Bag->GetStringField(TEXT("logLevel"));
		Message = Bag->GetStringField(TEXT("message"));
		TimeStamp = Bag->GetStringField(TEXT("timeStamp"));	
	}
};


/**
 Description:
  Tail the logs of a microservice

Usage:
  Beamable.Tools project logs <service> [options]

Arguments:
  <service>  The name of the service to view logs for

Options:
  --reconnect                      If the service stops, and reconnect is enabled, then the logs command will wait for the service to restart and then reattach to logs [default: True]
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
class UBeamCliProjectLogsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectLogsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectLogsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
