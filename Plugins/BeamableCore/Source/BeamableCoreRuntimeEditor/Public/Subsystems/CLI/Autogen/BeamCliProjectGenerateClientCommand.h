#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectGenerateClientCommand.generated.h"


UCLASS(BlueprintType)
class UBeamCliProjectGenerateClientStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BeamoId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FilePath = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("filePath"), FilePath, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("beamoId"), BeamoId, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("filePath"), FilePath, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("beamoId")), BeamoId);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("filePath")), FilePath);	
	}
};


/**
 Description:
  [INTERNAL] Obsolete command, please use generate-client-oapi that used the OpenAPI specifications to generate the C# client code. The generate-client command will Generate a C# client file based on a built C# microservice dll directory using refactor

Usage:
  Beamable.Tools project generate-client <source> [options]

Arguments:
  <source>  The .dll filepath for the built microservice

Options:
  --ids <ids>                                          The list of services to include, defaults to all local services (separated by whitespace)
  --without-group, --without-groups <without-group>    A set of BeamServiceGroup tags that will exclude the associated services. Exclusion takes precedence over inclusion
  --with-group, --with-groups <with-group>             A set of BeamServiceGroup tags that will include the associated services
  --output-dir <output-dir>                            Directory to write the output client at
  --output-links                                       When true, generate the source client files to all associated projects [default: True]
  --output-unity-projects <output-unity-projects>      Paths to unity projects to generate clients in
  --existing-fed-ids <existing-fed-ids>                A set of existing federation ids
  --existing-fed-type-names <existing-fed-type-names>  A set of existing class names for federations (Obsolete)
  --output-path-hints <output-path-hints>              A special format, BEAMOID=PATH, that tells the generator where to place the client. The path should be relative to the linked project root (Obsolete)
  --dryrun                                             [DEPRECATED] Run as much of the command as possible without making any network calls
  --cid <cid>                                          CID (CustomerId) to use (found in Portal->Account); defaults to whatever is in '.beamable/connection-configuration.json'
  --pid <pid>                                          PID (Realm ID) to use (found in Portal -> Games -> Any Realm's details); defaults to whatever is in '.beamable/connection-configuration.json'
  -q, --quiet                                          When true, skip input waiting and use default arguments (or error if no defaults are possible) [default: False]
  --host <host>                                        This option defines the target Beamable environment. Needed for private cloud customers to target their exclusive Beamable environment. Ignorable by everyone else. Stored in '.beamable/connection-configuration.json'
  --access-token <access-token>                        The access token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --refresh-token <refresh-token>                      A Refresh Token to use for the requests. It overwrites the logged in user stored in connection-auth.json for THIS INVOCATION ONLY
  --log, --logs <log>                                  Extra logs gets printed out
  --no-redirect                                        If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  -prf, --prefer-remote-federation                     By default, any local CLI invocation that should trigger a Federation of any type will prefer locally running Microservices. However, if you need the CLI to use the remotely running Microservices, use this option to ignore locally running services.
  --unmask-logs                                        By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                                        By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>                  a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                                       Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                                   Out all log messages as data payloads in addition to however they are logged
  --add-project-path <add-project-path>                additional file paths to be included when building a local project manifest.
  --dir <dir>                                          [DEPRECATED] Path override for the .beamable folder
  --raw                                                Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                             Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                          a custom location for dotnet [default: dotnet]
  -?, -h, --help                                       Show help and usage information




 */
UCLASS()
class UBeamCliProjectGenerateClientCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectGenerateClientStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (TArray<UBeamCliProjectGenerateClientStreamData*>& StreamData, TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
