#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServerServeCommand.generated.h"


UCLASS()
class UBeamCliServerServeStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	int32 Port = {};
	UPROPERTY()
	FString Uri = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("port"), Port);
		Serializer->WriteValue(TEXT("uri"), Uri);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("port"), Port);
		Serializer->WriteValue(TEXT("uri"), Uri);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Port = Bag->GetIntegerField(TEXT("port"));
		Uri = Bag->GetStringField(TEXT("uri"));	
	}
};


/**
 Description:
  [INTERNAL] Create a local server for the cli

Usage:
  Beamable.Tools server serve [<owner>] [options]

Arguments:
  <owner>  The owner of the server is used to identify the server later with the /info endpoint [default: cli]

Options:
  -p, --port <port>                                    The port the local server will bind to [default: 8342]
  -i, --auto-inc-port                                  When true, if the given --port is not available, it will be incremented until an available port is discovered [default: True]
  -d, --self-destruct-seconds <self-destruct-seconds>  The number of seconds the server will stay alive without receiving any traffic. A value of zero means there is no self destruct timer [default: 0]
  --dryrun                                             Should any networking happen?
  --cid <cid>                                          Cid to use; will default to whatever is in the file system
  --pid <pid>                                          Pid to use; will default to whatever is in the file system
  -q, --quiet                                          When true, skip input waiting and use defaults [default: False]
  --host <host>                                        The host endpoint for beamable
  --refresh-token <refresh-token>                      Refresh token to use for the requests
  --log, --logs <log>                                  Extra logs gets printed out
  --dir <dir>                                          Directory to use for configuration
  --raw                                                Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                             Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                          a custom location for dotnet
  -?, -h, --help                                       Show help and usage information




 */
UCLASS()
class UBeamCliServerServeCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServerServeStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServerServeStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
