#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectPsCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectPsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Cid = {};
	UPROPERTY()
	FString Pid = {};
	UPROPERTY()
	FString Prefix = {};
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	bool IsRunning = {};
	UPROPERTY()
	bool IsContainer = {};
	UPROPERTY()
	FString ServiceType = {};
	UPROPERTY()
	int32 HealthPort = {};
	UPROPERTY()
	int32 DataPort = {};
	UPROPERTY()
	FString ContainerId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("prefix"), Prefix);
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("isRunning"), IsRunning);
		Serializer->WriteValue(TEXT("isContainer"), IsContainer);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("dataPort"), DataPort);
		Serializer->WriteValue(TEXT("containerId"), ContainerId);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("prefix"), Prefix);
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("isRunning"), IsRunning);
		Serializer->WriteValue(TEXT("isContainer"), IsContainer);
		Serializer->WriteValue(TEXT("serviceType"), ServiceType);
		Serializer->WriteValue(TEXT("healthPort"), HealthPort);
		Serializer->WriteValue(TEXT("dataPort"), DataPort);
		Serializer->WriteValue(TEXT("containerId"), ContainerId);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Cid = Bag->GetStringField(TEXT("cid"));
		Pid = Bag->GetStringField(TEXT("pid"));
		Prefix = Bag->GetStringField(TEXT("prefix"));
		Service = Bag->GetStringField(TEXT("service"));
		IsRunning = Bag->GetBoolField(TEXT("isRunning"));
		IsContainer = Bag->GetBoolField(TEXT("isContainer"));
		ServiceType = Bag->GetStringField(TEXT("serviceType"));
		HealthPort = Bag->GetIntegerField(TEXT("healthPort"));
		DataPort = Bag->GetIntegerField(TEXT("dataPort"));
		ContainerId = Bag->GetStringField(TEXT("containerId"));	
	}
};


/**
 Description:
  List the running status of local services not running in docker

Usage:
  Beamable.Tools project ps [options]

Options:
  -w, --watch                      When true, the command will run forever and watch the state of the program
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
class UBeamCliProjectPsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectPsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectPsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
