#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesDeployCommand.generated.h"


UCLASS()
class UBeamCliServicesDeployStreamData : public UObject, public IBeamJsonSerializableUObject
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
class UBeamCliServicesDeployRemoteProgressStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString BeamoId = {};
	UPROPERTY()
	double BuildAndTestProgress = {};
	UPROPERTY()
	double ContainerUploadProgress = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("BeamoId"), BeamoId);
		Serializer->WriteValue(TEXT("BuildAndTestProgress"), BuildAndTestProgress);
		Serializer->WriteValue(TEXT("ContainerUploadProgress"), ContainerUploadProgress);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("BeamoId"), BeamoId);
		Serializer->WriteValue(TEXT("BuildAndTestProgress"), BuildAndTestProgress);
		Serializer->WriteValue(TEXT("ContainerUploadProgress"), ContainerUploadProgress);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BeamoId = Bag->GetStringField(TEXT("BeamoId"));
		BuildAndTestProgress = Bag->GetNumberField(TEXT("BuildAndTestProgress"));
		ContainerUploadProgress = Bag->GetNumberField(TEXT("ContainerUploadProgress"));	
	}
};


UCLASS()
class UBeamCliServicesDeployLogsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Message = {};
	UPROPERTY()
	FString Level = {};
	UPROPERTY()
	FString TimeStamp = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Message"), Message);
		Serializer->WriteValue(TEXT("Level"), Level);
		Serializer->WriteValue(TEXT("TimeStamp"), TimeStamp);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Message"), Message);
		Serializer->WriteValue(TEXT("Level"), Level);
		Serializer->WriteValue(TEXT("TimeStamp"), TimeStamp);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Message = Bag->GetStringField(TEXT("Message"));
		Level = Bag->GetStringField(TEXT("Level"));
		TimeStamp = Bag->GetStringField(TEXT("TimeStamp"));	
	}
};


/**
 Description:
  Deploys services remotely to the current realm

Usage:
  Beamable.Tools services deploy [options]

Options:
  --from-file <from-file>                      If this option is set to a valid path to a ServiceManifest JSON, deploys that instead []
  --comment <comment>                          Associates this comment along with the published Manifest. You'll be able to read it via the Beamable Portal []
  --service-comments <service-comments>        Any number of strings in the format BeamoId::Comment
                                               Associates each comment to the given Beamo Id if it's among the published services. You'll be able to read it via the Beamable Portal []
  --docker-registry-url <docker-registry-url>  A custom docker registry url to use when uploading. By default, the result from the beamo/registry network call will be used, with minor string manipulation to add https scheme, remove port specificatino, and add /v2
  --dryrun                                     Should any networking happen?
  --cid <cid>                                  Cid to use; will default to whatever is in the file system
  --pid <pid>                                  Pid to use; will default to whatever is in the file system
  -q, --quiet                                  When true, skip input waiting and use defaults [default: False]
  --host <host>                                The host endpoint for beamable
  --access-token <access-token>                The access token to use for the requests
  --refresh-token <refresh-token>              Refresh token to use for the requests
  --log, --logs <log>                          Extra logs gets printed out
  --no-redirect                                If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                                By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                                By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>          a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                               Currently, a docker path has been automatically identified. [default: docker]
  --dir <dir>                                  Directory to use for configuration
  --raw                                        Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                     Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                  a custom location for dotnet [default: dotnet]
  -?, -h, --help                               Show help and usage information



 */
UCLASS()
class UBeamCliServicesDeployCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesDeployStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesDeployStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeRemoteProgress = FString(TEXT("remote_progress"));
	UPROPERTY() TArray<UBeamCliServicesDeployRemoteProgressStreamData*> RemoteProgressStream;
	UPROPERTY() TArray<int64> RemoteProgressTimestamps;
	TFunction<void (const TArray<UBeamCliServicesDeployRemoteProgressStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnRemoteProgressStreamOutput;

	inline static FString StreamTypeLogs = FString(TEXT("logs"));
	UPROPERTY() TArray<UBeamCliServicesDeployLogsStreamData*> LogsStream;
	UPROPERTY() TArray<int64> LogsTimestamps;
	TFunction<void (const TArray<UBeamCliServicesDeployLogsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnLogsStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
