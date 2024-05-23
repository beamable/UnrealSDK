#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliUnityGetVersionInfoCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliUnityGetVersionInfoStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString BeamableNugetVersion = {};
	UPROPERTY()
	FString SdkVersion = {};
	UPROPERTY()
	FString PackageFolder = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamableNugetVersion"), BeamableNugetVersion);
		Serializer->WriteValue(TEXT("sdkVersion"), SdkVersion);
		Serializer->WriteValue(TEXT("packageFolder"), PackageFolder);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("beamableNugetVersion"), BeamableNugetVersion);
		Serializer->WriteValue(TEXT("sdkVersion"), SdkVersion);
		Serializer->WriteValue(TEXT("packageFolder"), PackageFolder);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		BeamableNugetVersion = Bag->GetStringField(TEXT("beamableNugetVersion"));
		SdkVersion = Bag->GetStringField(TEXT("sdkVersion"));
		PackageFolder = Bag->GetStringField(TEXT("packageFolder"));	
	}
};


/**
 Description:
  [INTERNAL] get information about a beamable unity sdk project's version dependencies

Usage:
  Beamable.Tools unity get-version-info <unityPath> [options]

Arguments:
  <unityPath>  the path to the root of the unity project

Options:
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
class UBeamCliUnityGetVersionInfoCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliUnityGetVersionInfoStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliUnityGetVersionInfoStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
