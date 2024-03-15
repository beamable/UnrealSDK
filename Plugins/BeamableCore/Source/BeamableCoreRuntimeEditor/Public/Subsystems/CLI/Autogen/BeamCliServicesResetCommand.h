#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliServicesResetCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliServicesResetStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Target = {};
	UPROPERTY()
	TArray<FString> Ids = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Target"), Target);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Ids"), Ids, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Target"), Target);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("Ids"), Ids, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Target = Bag->GetStringField(TEXT("Target"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("Ids")), Ids, OuterOwner);	
	}
};


/**
 Description:
  Resets services to default settings and cleans up docker images (if any exist)

Usage:
  Beamable.Tools services reset <target> [options]

Arguments:
  <target>  Either image|container|protocols.'image' will cleanup all your locally built images for the selected Beamo Services.
            'container' will stop all your locally running containers for the selected Beamo Services.
            'protocols' will reset all the protocol data for the selected Beamo Services back to default parameters

Options:
  --ids <ids>                      The ids for the services you wish to reset
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
class UBeamCliServicesResetCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliServicesResetStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliServicesResetStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
