#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesRunCommand.generated.h"


UCLASS()
class UBeamCliServicesRunStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool Success = {};
	UPROPERTY()
	FString FailureReason = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Success"), Success);
		Serializer->WriteValue(TEXT("FailureReason"), FailureReason);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Success"), Success);
		Serializer->WriteValue(TEXT("FailureReason"), FailureReason);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Success = Bag->GetBoolField(TEXT("Success"));
		FailureReason = Bag->GetStringField(TEXT("FailureReason"));	
	}
};


UCLASS()
class UBeamCliServicesRunLocalProgressStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString BeamoId = {};
	UPROPERTY()
	double LocalDeployProgress = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("BeamoId"), BeamoId);
		Serializer->WriteValue(TEXT("LocalDeployProgress"), LocalDeployProgress);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("BeamoId"), BeamoId);
		Serializer->WriteValue(TEXT("LocalDeployProgress"), LocalDeployProgress);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BeamoId = Bag->GetStringField(TEXT("BeamoId"));
		LocalDeployProgress = Bag->GetNumberField(TEXT("LocalDeployProgress"));	
	}
};


/**
 Description:
  Run services locally in Docker. Will fail if no docker instance is running in the local machine

Usage:
  Beamable.Tools services run [options]

Options:
  --ids <ids>                      The ids for the services you wish to deploy. Ignoring this option deploys all services
  -fcpu, --force-amd-cpu-arch      Force the services to run with amd64 CPU architecture, useful when deploying from computers with ARM architecture [default: False]
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
class UBeamCliServicesRunCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesRunStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesRunStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeLocalProgress = FString(TEXT("local_progress"));
	UPROPERTY() TArray<UBeamCliServicesRunLocalProgressStreamData*> LocalProgressStream;
	UPROPERTY() TArray<int64> LocalProgressTimestamps;
	TFunction<void (const TArray<UBeamCliServicesRunLocalProgressStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnLocalProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
