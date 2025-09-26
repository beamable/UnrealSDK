#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliInitCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliInitStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Host = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Pid = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("host"), Host, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("host"), Host, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("host"), Bag, Host);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cid"), Bag, Cid);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("pid"), Bag, Pid);	
	}
};


UCLASS(BlueprintType)
class UBeamCliInitErrorLoginFailedErrorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
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
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("invocation"), Bag, Invocation);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("exitCode"), Bag, ExitCode);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("typeName"), Bag, TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("fullTypeName"), Bag, FullTypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stackTrace"), Bag, StackTrace);	
	}
};


UCLASS(BlueprintType)
class UBeamCliInitErrorInvalidCidErrorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
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
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("invocation"), Invocation, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("exitCode"), ExitCode, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullTypeName"), FullTypeName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("stackTrace"), StackTrace, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("invocation"), Bag, Invocation);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("exitCode"), Bag, ExitCode);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("typeName"), Bag, TypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("fullTypeName"), Bag, FullTypeName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stackTrace"), Bag, StackTrace);	
	}
};


/**
 Description:
  Initialize a new Beamable project in the current directory

Usage:
  Beamable.Tools init [<path>] [options]

Arguments:
  <path>  the folder that will be initialized as a beamable project.  [default: .]

Options:
  --email, --username <email>                Specify user email address
  --password <password>                      User password
  --host <host>                              This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --refresh-token <refresh-token>            A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --ignore-pid                               Ignore the existing pid while initializing
  --save-extra-paths <save-extra-paths>      Overwrite the stored extra paths for where to find projects []
  --paths-to-ignore <paths-to-ignore>        Paths to ignore when searching for services []
  --save-to-environment                      Save login refresh token to environment variable
  --no-token-save                            Prevent auth tokens from being saved to disk. This replaces the legacy --save-to-file option [default: False]
  --realm-scoped                             Makes the resulting access/refresh token pair be realm scoped instead of the default customer scoped one
  --print-to-console                         Prints out login request response to console
  --dryrun                                   [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                                CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --engine <engine>                          If passed, sets the engine integration that is calling for the command
  --engine-sdk-version <engine-sdk-version>  The version of the Beamable's SDK running in that Engine
  --engine-version <engine-version>          The version of the engine that is calling the CLI
  --pid <pid>                                PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                                When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                              This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>              The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>            A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                        Extra logs gets printed out
  --no-redirect                              If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation           By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                              By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                              By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>        a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                             Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                         Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>      additional file paths to be included when building a local project manifest.
  --dir <dir>                                [DEPRECATED] Path override for the .beamable folder
  --raw                                      Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                   Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                a custom location for dotnet [default: dotnet]
  -?, -h, --help                             Show help and usage information




 */
UCLASS()
class UBeamCliInitCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliInitStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (TArray<UBeamCliInitStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeErrorLoginFailedError = FString(TEXT("errorLoginFailedError"));
	UPROPERTY() TArray<UBeamCliInitErrorLoginFailedErrorStreamData*> ErrorLoginFailedErrorStream;
	UPROPERTY() TArray<int64> ErrorLoginFailedErrorTimestamps;
	TFunction<void (TArray<UBeamCliInitErrorLoginFailedErrorStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnErrorLoginFailedErrorStreamOutput;

	inline static FString StreamTypeErrorInvalidCidError = FString(TEXT("errorInvalidCidError"));
	UPROPERTY() TArray<UBeamCliInitErrorInvalidCidErrorStreamData*> ErrorInvalidCidErrorStream;
	UPROPERTY() TArray<int64> ErrorInvalidCidErrorTimestamps;
	TFunction<void (TArray<UBeamCliInitErrorInvalidCidErrorStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnErrorInvalidCidErrorStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
