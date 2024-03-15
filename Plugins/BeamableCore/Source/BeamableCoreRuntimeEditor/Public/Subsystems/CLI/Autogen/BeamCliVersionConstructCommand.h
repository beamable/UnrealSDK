#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliVersionConstructCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliVersionConstructStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString VersionString = {};
	UPROPERTY()
	FString VersionPrefix = {};
	UPROPERTY()
	FString VersionSuffix = {};
	UPROPERTY()
	bool Exists = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("versionString"), VersionString);
		Serializer->WriteValue(TEXT("versionPrefix"), VersionPrefix);
		Serializer->WriteValue(TEXT("versionSuffix"), VersionSuffix);
		Serializer->WriteValue(TEXT("exists"), Exists);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("versionString"), VersionString);
		Serializer->WriteValue(TEXT("versionPrefix"), VersionPrefix);
		Serializer->WriteValue(TEXT("versionSuffix"), VersionSuffix);
		Serializer->WriteValue(TEXT("exists"), Exists);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		VersionString = Bag->GetStringField(TEXT("versionString"));
		VersionPrefix = Bag->GetStringField(TEXT("versionPrefix"));
		VersionSuffix = Bag->GetStringField(TEXT("versionSuffix"));
		Exists = Bag->GetBoolField(TEXT("exists"));	
	}
};


/**
 Description:
  [INTERNAL] constructs a beamable version string with the given configuration

Usage:
  Beamable.Tools version construct <major> <minor> <patch> [options]

Arguments:
  <major>  The major semantic version number
  <minor>  The minor semantic version number
  <patch>  The patch semantic version number

Options:
  --validate                       When true, the command will return a non zero exit code if the specified version already exists on Nuget
  --nightly                        Sets the version string to a nightly version number, and will include the date string automatically
  --rc <rc>                        Sets the version string to a release candidate version number
  --exp <exp>                      Sets the version string to an experimental version number
  --prod                           Sets the version string to a production version number
  --dryrun                         Should any networking happen?
  --cid <cid>                      Cid to use; will default to whatever is in the file system
  --pid <pid>                      Pid to use; will default to whatever is in the file system
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
class UBeamCliVersionConstructCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliVersionConstructStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliVersionConstructStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
