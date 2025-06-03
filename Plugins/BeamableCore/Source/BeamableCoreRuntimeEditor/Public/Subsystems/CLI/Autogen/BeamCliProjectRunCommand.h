#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportBuildErrorsStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultBuildErrorsStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/RunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportErrorRunFailErrorOutputStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultErrorRunFailErrorOutputStreamData.h"
#include "BeamCliProjectRunCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliProjectRunStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProgressRatio = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("progressRatio"), ProgressRatio, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("progressRatio"), ProgressRatio, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceId")), ServiceId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("message")), Message);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("progressRatio")), ProgressRatio);	
	}
};


UCLASS(BlueprintType)
class UBeamCliProjectRunBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServiceId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectErrorReportBuildErrorsStreamData* Report = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceId"), ServiceId, Serializer);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceId")), ServiceId);
		UBeamJsonUtils::DeserializeUObject<UProjectErrorReportBuildErrorsStreamData*>("report", Bag, Report, OuterOwner);	
	}
};


UCLASS(BlueprintType)
class UBeamCliProjectRunErrorRunFailErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*> CompilerErrors = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Invocation = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExitCode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TypeName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FullTypeName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StackTrace = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(TEXT("compilerErrors"), CompilerErrors, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(TEXT("compilerErrors"), CompilerErrors, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<URunProjectBuildErrorStreamErrorRunFailErrorOutputStreamData*>(Bag->GetArrayField(TEXT("compilerErrors")), CompilerErrors, OuterOwner);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("message")), Message);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("invocation")), Invocation);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("exitCode")), ExitCode);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("typeName")), TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("fullTypeName")), FullTypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stackTrace")), StackTrace);	
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
  --no-client-gen                                    We compile services that need compiling before running. This will disable the client-code generation part of the compilation
  --require-process-id <require-process-id>          Forwards the given process-id to the BEAM_REQUIRE_PROCESS_ID environment variable of the running Microservice. The Microservice will self-destruct if the given process exits
  --dryrun                                           [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                                        CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --pid <pid>                                        PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                                        When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                                      This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>                      The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>                    A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                                Extra logs gets printed out
  --no-redirect                                      If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation                   By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                                      By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                                      By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>                a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                                     Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                                 Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>              additional file paths to be included when building a local project manifest.
  --dir <dir>                                        [DEPRECATED] Path override for the .beamable folder
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
	TFunction<void (TArray<UBeamCliProjectRunStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeBuildErrors = FString(TEXT("buildErrors"));
	UPROPERTY() TArray<UBeamCliProjectRunBuildErrorsStreamData*> BuildErrorsStream;
	UPROPERTY() TArray<int64> BuildErrorsTimestamps;
	TFunction<void (TArray<UBeamCliProjectRunBuildErrorsStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnBuildErrorsStreamOutput;

	inline static FString StreamTypeErrorRunFailErrorOutput = FString(TEXT("errorRunFailErrorOutput"));
	UPROPERTY() TArray<UBeamCliProjectRunErrorRunFailErrorOutputStreamData*> ErrorRunFailErrorOutputStream;
	UPROPERTY() TArray<int64> ErrorRunFailErrorOutputTimestamps;
	TFunction<void (TArray<UBeamCliProjectRunErrorRunFailErrorOutputStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnErrorRunFailErrorOutputStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
