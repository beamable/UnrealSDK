#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportBuildErrorsStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultBuildErrorsStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportErrorRunFailErrorOutputStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultErrorRunFailErrorOutputStreamData.h"
#include "BeamCliProjectRunCommand.generated.h"


UCLASS()
class UBeamCliProjectRunStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ServiceId = {};
	UPROPERTY()
	FString Message = {};
	UPROPERTY()
	float ProgressRatio = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceId"), ServiceId);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("progressRatio"), ProgressRatio);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceId"), ServiceId);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("progressRatio"), ProgressRatio);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceId = Bag->GetStringField(TEXT("serviceId"));
		Message = Bag->GetStringField(TEXT("message"));
		FDefaultValueHelper::ParseFloat(Bag->GetStringField(TEXT("progressRatio")), ProgressRatio);	
	}
};


UCLASS()
class UBeamCliProjectRunBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString ServiceId = {};
	UPROPERTY()
	UProjectErrorReportBuildErrorsStreamData* Report = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceId"), ServiceId);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("serviceId"), ServiceId);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		ServiceId = Bag->GetStringField(TEXT("serviceId"));
		UBeamJsonUtils::DeserializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Bag, Report, OuterOwner);	
	}
};


UCLASS()
class UBeamCliProjectRunErrorRunFailErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*> CompilerErrors = {};
	UPROPERTY()
	FString Message = {};
	UPROPERTY()
	FString Invocation = {};
	UPROPERTY()
	int32 ExitCode = {};
	UPROPERTY()
	FString TypeName = {};
	UPROPERTY()
	FString FullTypeName = {};
	UPROPERTY()
	FString StackTrace = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(TEXT("compilerErrors"), CompilerErrors, Serializer);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("invocation"), Invocation);
		Serializer->WriteValue(TEXT("exitCode"), ExitCode);
		Serializer->WriteValue(TEXT("typeName"), TypeName);
		Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
		Serializer->WriteValue(TEXT("stackTrace"), StackTrace);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(TEXT("compilerErrors"), CompilerErrors, Serializer);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("invocation"), Invocation);
		Serializer->WriteValue(TEXT("exitCode"), ExitCode);
		Serializer->WriteValue(TEXT("typeName"), TypeName);
		Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
		Serializer->WriteValue(TEXT("stackTrace"), StackTrace);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(Bag->GetArrayField(TEXT("compilerErrors")), CompilerErrors, OuterOwner);
		Message = Bag->GetStringField(TEXT("message"));
		Invocation = Bag->GetStringField(TEXT("invocation"));
		ExitCode = Bag->GetIntegerField(TEXT("exitCode"));
		TypeName = Bag->GetStringField(TEXT("typeName"));
		FullTypeName = Bag->GetStringField(TEXT("fullTypeName"));
		StackTrace = Bag->GetStringField(TEXT("stackTrace"));	
	}
};


/**
 Description:
  Run a project

Usage:
  Beamable.Tools project run [options]

Options:
  -w, --watch                                        When true, the command will run forever and watch the state of the program
  --ids <ids>                                        The list of services to include, defaults to all local services (separated by whitespace)
  --without-group, --without-groups <without-group>  A set of BeamServiceGroup tags that will exclude the associated services. Exclusion takes precedence over inclusion
  --with-group, --with-groups <with-group>           A set of BeamServiceGroup tags that will include the associated services
  --force                                            With this flag, we restart any running services. Without it, we skip running services
  --detach                                           With this flag, the service will run the background after it has reached basic startup
  --dryrun                                           Should any networking happen?
  --cid <cid>                                        Cid to use; will default to whatever is in the file system
  --pid <pid>                                        Pid to use; will default to whatever is in the file system
  -q, --quiet                                        When true, skip input waiting and use defaults [default: False]
  --host <host>                                      The host endpoint for beamable
  --access-token <access-token>                      The access token to use for the requests
  --refresh-token <refresh-token>                    Refresh token to use for the requests
  --log, --logs <log>                                Extra logs gets printed out
  --no-redirect                                      If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                                      By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                                      By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>                a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                                     Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                                 Out all log messages as data payloads in addition to however they are logged
  --dir <dir>                                        Directory to use for configuration
  --raw                                              Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                           Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                        a custom location for dotnet [default: dotnet]
  -?, -h, --help                                     Show help and usage information



 */
UCLASS()
class UBeamCliProjectRunCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectRunStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectRunStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeBuildErrors = FString(TEXT("buildErrors"));
	UPROPERTY() TArray<UBeamCliProjectRunBuildErrorsStreamData*> BuildErrorsStream;
	UPROPERTY() TArray<int64> BuildErrorsTimestamps;
	TFunction<void (const TArray<UBeamCliProjectRunBuildErrorsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnBuildErrorsStreamOutput;

	inline static FString StreamTypeErrorRunFailErrorOutput = FString(TEXT("errorRunFailErrorOutput"));
	UPROPERTY() TArray<UBeamCliProjectRunErrorRunFailErrorOutputStreamData*> ErrorRunFailErrorOutputStream;
	UPROPERTY() TArray<int64> ErrorRunFailErrorOutputTimestamps;
	TFunction<void (const TArray<UBeamCliProjectRunErrorRunFailErrorOutputStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnErrorRunFailErrorOutputStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
