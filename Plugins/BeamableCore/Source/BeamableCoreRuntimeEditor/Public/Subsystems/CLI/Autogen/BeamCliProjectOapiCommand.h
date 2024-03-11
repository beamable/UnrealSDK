#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectOapiCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliProjectOapiStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	bool IsBuilt = {};
	UPROPERTY()
	FString OpenApi = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("isBuilt"), IsBuilt);
		Serializer->WriteValue(TEXT("openApi"), OpenApi);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("isBuilt"), IsBuilt);
		Serializer->WriteValue(TEXT("openApi"), OpenApi);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		IsBuilt = Bag->GetBoolField(TEXT("isBuilt"));
		OpenApi = Bag->GetStringField(TEXT("openApi"));	
	}
};


/**
 Description:
  Generate the Open API specification for the project

Usage:
  Beamable.Tools project oapi [options]

Options:
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
class UBeamCliProjectOapiCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectOapiStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectOapiStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
