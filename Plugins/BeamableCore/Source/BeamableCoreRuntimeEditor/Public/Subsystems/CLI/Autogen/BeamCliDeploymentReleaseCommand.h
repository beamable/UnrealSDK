#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/DeployablePlanStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ManifestViewStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalStringStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalLongStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceComponentStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceDependencyReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/OptionalArrayOfServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceStorageReferenceStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DeploymentDiffSummaryStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/DeploymentManifestJsonDiffStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceFederationChangeStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ServiceImageIdChangeStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportBuildErrorsStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultBuildErrorsStreamData.h"
#include "BeamCliDeploymentReleaseCommand.generated.h"


UCLASS()
class UBeamCliDeploymentReleaseStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	bool Success = {};
	UPROPERTY()
	UDeployablePlanStreamData* Plan = {};
	UPROPERTY()
	FString PlanPath = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("success"), Success);
		UBeamJsonUtils::SerializeUObject<UDeployablePlanStreamData*>("plan", Plan, Serializer);
		Serializer->WriteValue(TEXT("planPath"), PlanPath);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("success"), Success);
		UBeamJsonUtils::SerializeUObject<UDeployablePlanStreamData*>("plan", Plan, Serializer);
		Serializer->WriteValue(TEXT("planPath"), PlanPath);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Success = Bag->GetBoolField(TEXT("success"));
		UBeamJsonUtils::DeserializeUObject<UDeployablePlanStreamData*>("plan", Bag, Plan, OuterOwner);
		PlanPath = Bag->GetStringField(TEXT("planPath"));	
	}
};


UCLASS()
class UBeamCliDeploymentReleaseBuildErrorsStreamData : public UObject, public IBeamJsonSerializableUObject
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
class UBeamCliDeploymentReleaseProgressStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Name = {};
	UPROPERTY()
	float Ratio = {};
	UPROPERTY()
	bool IsKnownLength = {};
	UPROPERTY()
	FString ServiceName = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("ratio"), Ratio);
		Serializer->WriteValue(TEXT("isKnownLength"), IsKnownLength);
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("ratio"), Ratio);
		Serializer->WriteValue(TEXT("isKnownLength"), IsKnownLength);
		Serializer->WriteValue(TEXT("serviceName"), ServiceName);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		FDefaultValueHelper::ParseFloat(Bag->GetStringField(TEXT("ratio")), Ratio);
		IsKnownLength = Bag->GetBoolField(TEXT("isKnownLength"));
		ServiceName = Bag->GetStringField(TEXT("serviceName"));	
	}
};


/**
 Description:
  Perform a release, this will modify remote running services

Usage:
  Beamable.Tools deployment release [options]

Options:
  -c, --comment <comment>                                   Associates this comment along with the published Manifest. You'll be able to read it via the Beamable Portal []
  -sc, --service-comments <service-comments>                Any number of strings in the format BeamoId::Comment
                                                            Associates each comment to the given Beamo Id if it's among the published services. You'll be able to read it via the Beamable Portal []
  -m, --from-manifest, --manifest <from-manifest>           A manifest json file to use to create a plan
  -i, --from-manifest-id, --manifest-id <from-manifest-id>  A manifest id to download and use to create a plan
  -h, --health, --run-health-checks                         Run health checks on services
  --redeploy, --restart, --roll                             Restart existing deployed services
  --merge                                                   Create a Release that adds your current local environment to the existing remote services. Existing deployed services will not be removed
  --replace                                                 Create a Release that completely overrides the existing remote services. Existing deployed services that are not present locally will be removed (default)
  -p, --from-plan, --plan <from-plan>                       The file path to a pre-generated plan file using the `deploy plan` command
  -lp, --from-latest-plan, --last-plan, --latest-plan       Use the most recent plan generated from the plan command
  --dryrun                                                  Should any networking happen?
  --cid <cid>                                               Cid to use; will default to whatever is in the file system
  --pid <pid>                                               Pid to use; will default to whatever is in the file system
  -q, --quiet                                               When true, skip input waiting and use defaults [default: False]
  --host <host>                                             The host endpoint for beamable
  --access-token <access-token>                             The access token to use for the requests
  --refresh-token <refresh-token>                           Refresh token to use for the requests
  --log, --logs <log>                                       Extra logs gets printed out
  --no-redirect                                             If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                                             By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                                             By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>                       a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                                            Currently, a docker path has been automatically identified. [default: docker]
  --emit-log-streams                                        Out all log messages as data payloads in addition to however they are logged
  --dir <dir>                                               Directory to use for configuration
  --raw                                                     Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                                  Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                               a custom location for dotnet [default: dotnet]
  -?, -h, --help                                            Show help and usage information



 */
UCLASS()
class UBeamCliDeploymentReleaseCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliDeploymentReleaseStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliDeploymentReleaseStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;

	inline static FString StreamTypeBuildErrors = FString(TEXT("buildErrors"));
	UPROPERTY() TArray<UBeamCliDeploymentReleaseBuildErrorsStreamData*> BuildErrorsStream;
	UPROPERTY() TArray<int64> BuildErrorsTimestamps;
	TFunction<void (const TArray<UBeamCliDeploymentReleaseBuildErrorsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnBuildErrorsStreamOutput;

	inline static FString StreamTypeProgress = FString(TEXT("progress"));
	UPROPERTY() TArray<UBeamCliDeploymentReleaseProgressStreamData*> ProgressStream;
	UPROPERTY() TArray<int64> ProgressTimestamps;
	TFunction<void (const TArray<UBeamCliDeploymentReleaseProgressStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnProgressStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual bool HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
