#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorReportStreamData.h"
#include "Subsystems/CLI/Autogen/StreamData/ProjectErrorResultStreamData.h"
#include "BeamCliProjectBuildCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectBuildStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	UProjectErrorReportStreamData* Report = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		UBeamJsonUtils::SerializeUObject<UProjectErrorReportStreamData*>("report", Report, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		UBeamJsonUtils::DeserializeUObject<UProjectErrorReportStreamData*>("report", Bag, Report, OuterOwner);	
	}
};


/**
 Description:
  Build and monitor for compile errors

Usage:
  Beamable.Tools project build [options]

Options:
  -w, --watch                      When true, the command will run forever and watch the state of the program
  --ids <ids>                      The list of services to build, defaults to all local services
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
class UBeamCliProjectBuildCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectBuildStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectBuildStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
