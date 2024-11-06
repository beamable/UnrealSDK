#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliTokenInspectCommand.generated.h"


UCLASS()
class UBeamCliTokenInspectStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool WasRefreshToken = {};
	UPROPERTY()
	int64 AccountId = {};
	UPROPERTY()
	int64 Cid = {};
	UPROPERTY()
	int64 Created = {};
	UPROPERTY()
	FString Device = {};
	UPROPERTY()
	int64 ExpiresMs = {};
	UPROPERTY()
	int64 GamerTag = {};
	UPROPERTY()
	FString Pid = {};
	UPROPERTY()
	FString Platform = {};
	UPROPERTY()
	bool Revoked = {};
	UPROPERTY()
	TArray<FString> Scopes = {};
	UPROPERTY()
	FString Token = {};
	UPROPERTY()
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


UCLASS()
class UBeamCliTokenInspectErrorInvalidTokenErrorOutputStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString RefreshToken = {};
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
  --dryrun                               Should any networking happen?
  --cid <cid>                            Cid to use; will default to whatever is in the file system
  --pid <pid>                            Pid to use; will default to whatever is in the file system
  -q, --quiet                            When true, skip input waiting and use defaults [default: False]
  --host <host>                          The host endpoint for beamable
  --access-token <access-token>          The access token to use for the requests
  --refresh-token <refresh-token>        Refresh token to use for the requests
  --log, --logs <log>                    Extra logs gets printed out
  --no-redirect                          If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                          By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                          By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>    a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                         Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                     Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>  additional file paths to be included when building a local project manifest.
  --dir <dir>                            Directory to use for configuration
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
