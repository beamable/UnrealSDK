#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/GetLogsUrlHeaderStreamData.h"
#include "BeamCliServicesServiceMetricsCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliServicesServiceMetricsStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<UGetLogsUrlHeaderStreamData*> Headers = {};
	UPROPERTY()
	FString Url = {};
	UPROPERTY()
	FString Body = {};
	UPROPERTY()
	FString Method = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UGetLogsUrlHeaderStreamData*>(TEXT("headers"), Headers, Serializer);
		Serializer->WriteValue(TEXT("url"), Url);
		Serializer->WriteValue(TEXT("body"), Body);
		Serializer->WriteValue(TEXT("method"), Method);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<UGetLogsUrlHeaderStreamData*>(TEXT("headers"), Headers, Serializer);
		Serializer->WriteValue(TEXT("url"), Url);
		Serializer->WriteValue(TEXT("body"), Body);
		Serializer->WriteValue(TEXT("method"), Method);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UGetLogsUrlHeaderStreamData*>(Bag->GetArrayField(TEXT("headers")), Headers, OuterOwner);
		Url = Bag->GetStringField(TEXT("url"));
		Body = Bag->GetStringField(TEXT("body"));
		Method = Bag->GetStringField(TEXT("method"));	
	}
};


/**
 Description:
  Gets the URL that we can use to see the metrics for our services

Usage:
  Beamable.Tools services service-metrics [options]

Options:
  --id <id>                        The Unique Id for this service within this Beamable CLI context
  --metric <metric>                Set to 'cpu' or 'memory'
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
class UBeamCliServicesServiceMetricsCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesServiceMetricsStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesServiceMetricsStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
