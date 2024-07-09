#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/SetEnabledCommandComponentStreamData.h"
#include "BeamCliProjectEnableCommand.generated.h"


UCLASS()
class UBeamCliProjectEnableStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	TArray<USetEnabledCommandComponentStreamData*> ModifiedServices = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<USetEnabledCommandComponentStreamData*>(TEXT("modifiedServices"), ModifiedServices, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray<USetEnabledCommandComponentStreamData*>(TEXT("modifiedServices"), ModifiedServices, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<USetEnabledCommandComponentStreamData*>(Bag->GetArrayField(TEXT("modifiedServices")), ModifiedServices, OuterOwner);	
	}
};


/**
 Description:
  Enables a project. This modifies the BeamEnabled setting in the given project files

Usage:
  Beamable.Tools project enable [options]

Options:
  --ids <ids>                                        The list of services to include, defaults to all local services
  --without-group, --without-groups <without-group>  A set of BeamServiceGroup tags that will exclude the associated services. Exclusion takes precedence over inclusion
  --with-group, --with-groups <with-group>           A set of BeamServiceGroup tags that will include the associated services
  --dryrun                                           Should any networking happen?
  --cid <cid>                                        Cid to use; will default to whatever is in the file system
  --pid <pid>                                        Pid to use; will default to whatever is in the file system
  -q, --quiet                                        When true, skip input waiting and use defaults [default: False]
  --host <host>                                      The host endpoint for beamable
  --refresh-token <refresh-token>                    Refresh token to use for the requests
  --log, --logs <log>                                Extra logs gets printed out
  --dir <dir>                                        Directory to use for configuration
  --raw                                              Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                           Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>                        a custom location for dotnet
  -?, -h, --help                                     Show help and usage information



 */
UCLASS()
class UBeamCliProjectEnableCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliProjectEnableStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliProjectEnableStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
