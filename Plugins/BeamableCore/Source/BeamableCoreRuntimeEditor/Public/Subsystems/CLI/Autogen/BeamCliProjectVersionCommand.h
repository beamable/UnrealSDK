#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectVersionCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectVersionStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<FString> ProjectPaths = {};
	UPROPERTY()
	TArray<FString> PackageNames = {};
	UPROPERTY()
	TArray<FString> PackageVersions = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("projectPaths"), ProjectPaths, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageNames"), PackageNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageVersions"), PackageVersions, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<FString>(TEXT("projectPaths"), ProjectPaths, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageNames"), PackageNames, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("packageVersions"), PackageVersions, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("projectPaths")), ProjectPaths, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("packageNames")), PackageNames, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("packageVersions")), PackageVersions, OuterOwner);	
	}
};


/**
 Description:
  Commands that lists Beamable package versions of a SAMS projects

Usage:
  Beamable.Tools project version [options]

Options:
  --requested-version <requested-version>  Request specific version of Beamable packages
  --dryrun                                 Should any networking happen?
  --cid <cid>                              Cid to use; will default to whatever is in the file system
  --pid <pid>                              Pid to use; will default to whatever is in the file system
  --host <host>                            The host endpoint for beamable
  --refresh-token <refresh-token>          Refresh token to use for the requests
  --log, --logs <log>                      Extra logs gets printed out
  --dir <dir>                              Directory to use for configuration
  --raw                                    Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                 Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>              a custom location for dotnet
  -?, -h, --help                           Show help and usage information



 */
UCLASS()
class UBeamCliProjectVersionCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectVersionStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectVersionStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
