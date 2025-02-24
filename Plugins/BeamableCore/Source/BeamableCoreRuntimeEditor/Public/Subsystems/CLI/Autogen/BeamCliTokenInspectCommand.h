#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliTokenInspectCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliTokenInspectStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool WasRefreshToken = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 AccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Device = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 ExpiresMs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 GamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Platform = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Revoked = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Scopes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Token = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("wasRefreshToken"), WasRefreshToken);
		Serializer->WriteValue(TEXT("accountId"), AccountId);
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("created"), Created);
		Serializer->WriteValue(TEXT("device"), Device);
		Serializer->WriteValue(TEXT("expiresMs"), ExpiresMs);
		Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("platform"), Platform);
		Serializer->WriteValue(TEXT("revoked"), Revoked);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
		Serializer->WriteValue(TEXT("token"), Token);
		Serializer->WriteValue(TEXT("type"), Type);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("wasRefreshToken"), WasRefreshToken);
		Serializer->WriteValue(TEXT("accountId"), AccountId);
		Serializer->WriteValue(TEXT("cid"), Cid);
		Serializer->WriteValue(TEXT("created"), Created);
		Serializer->WriteValue(TEXT("device"), Device);
		Serializer->WriteValue(TEXT("expiresMs"), ExpiresMs);
		Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("platform"), Platform);
		Serializer->WriteValue(TEXT("revoked"), Revoked);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
		Serializer->WriteValue(TEXT("token"), Token);
		Serializer->WriteValue(TEXT("type"), Type);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		WasRefreshToken = Bag->GetBoolField(TEXT("wasRefreshToken"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("accountId")), AccountId);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
		Device = Bag->GetStringField(TEXT("device"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("expiresMs")), ExpiresMs);
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
		Pid = Bag->GetStringField(TEXT("pid"));
		Platform = Bag->GetStringField(TEXT("platform"));
		Revoked = Bag->GetBoolField(TEXT("revoked"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
		Token = Bag->GetStringField(TEXT("token"));
		Type = Bag->GetStringField(TEXT("type"));	
	}
};


UCLASS(BlueprintType)
class UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RefreshToken = {};
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
		Serializer->WriteValue(TEXT("refreshToken"), RefreshToken);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("invocation"), Invocation);
		Serializer->WriteValue(TEXT("exitCode"), ExitCode);
		Serializer->WriteValue(TEXT("typeName"), TypeName);
		Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
		Serializer->WriteValue(TEXT("stackTrace"), StackTrace);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("refreshToken"), RefreshToken);
		Serializer->WriteValue(TEXT("message"), Message);
		Serializer->WriteValue(TEXT("invocation"), Invocation);
		Serializer->WriteValue(TEXT("exitCode"), ExitCode);
		Serializer->WriteValue(TEXT("typeName"), TypeName);
		Serializer->WriteValue(TEXT("fullTypeName"), FullTypeName);
		Serializer->WriteValue(TEXT("stackTrace"), StackTrace);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		RefreshToken = Bag->GetStringField(TEXT("refreshToken"));
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
  Get token information

Usage:
  Beamable.Tools token inspect [options]

Options:
  -r, --resolve                          This command normally only works for an access token. However, if this option is enabled and a refresh token is given, then it will be automatically converted to the access token and this command is rerun [default: False]
  -t, --token <token>                    The token that you want to get information for. This must be an access token. By default, the current access token of the .beamable context is used
  --dryrun                               [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                            CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --pid <pid>                            PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                            When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                          This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>          The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>        A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                    Extra logs gets printed out
  --no-redirect                          If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation       By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                          By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                          By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>    a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                         Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                     Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>  additional file paths to be included when building a local project manifest.
  --dir <dir>                            [DEPRECATED] Path override for the .beamable folder
  --raw                                  Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                               Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>            a custom location for dotnet [default: dotnet]
  -?, -h, --help                         Show help and usage information



 */
UCLASS()
class UBeamCliTokenInspectCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliTokenInspectStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliTokenInspectStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeErrorInvalidTokenErrorOutput = FString(TEXT("errorInvalidTokenErrorOutput"));
	UPROPERTY() TArray<UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData*> ErrorInvalidTokenErrorOutputStream;
	UPROPERTY() TArray<int64> ErrorInvalidTokenErrorOutputTimestamps;
	TFunction<void (const TArray<UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnErrorInvalidTokenErrorOutputStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
