#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"
#include "Subsystems/CLI/Autogen/StreamData/ExternalIdentityStreamData.h"
#include "BeamCliMeCommand.generated.h"

class FMonitoredProcess;


UCLASS()
class UBeamCliMeStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	int64 Id = {};
	UPROPERTY()
	FString Email = {};
	UPROPERTY()
	FString Language = {};
	UPROPERTY()
	TArray<FString> Scopes = {};
	UPROPERTY()
	TArray<FString> ThirdPartyAppAssociations = {};
	UPROPERTY()
	TArray<FString> DeviceIds = {};
	UPROPERTY()
	TArray<UExternalIdentityStreamData*> External = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("email"), Email);
		Serializer->WriteValue(TEXT("language"), Language);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("deviceIds"), DeviceIds, Serializer);
		UBeamJsonUtils::SerializeArray<UExternalIdentityStreamData*>(TEXT("external"), External, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("email"), Email);
		Serializer->WriteValue(TEXT("language"), Language);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("deviceIds"), DeviceIds, Serializer);
		UBeamJsonUtils::SerializeArray<UExternalIdentityStreamData*>(TEXT("external"), External, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
		Email = Bag->GetStringField(TEXT("email"));
		Language = Bag->GetStringField(TEXT("language"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("thirdPartyAppAssociations")), ThirdPartyAppAssociations, OuterOwner);
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("deviceIds")), DeviceIds, OuterOwner);
		UBeamJsonUtils::DeserializeArray<UExternalIdentityStreamData*>(Bag->GetArrayField(TEXT("external")), External, OuterOwner);	
	}
};


/**
 Description:
  Fetch the current account

Usage:
  Beamable.Tools me [options]

Options:
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
class UBeamCliMeCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
	inline static FString StreamType = FString(TEXT("stream"));
	UPROPERTY() TArray<UBeamCliMeStreamData*> Stream;
	UPROPERTY() TArray<int64> Timestamps;
	TFunction<void (const TArray<UBeamCliMeStreamData*>& StreamData, const TArray<int64>& Timestamps, const FBeamOperationHandle& Op)> OnStreamOutput;	

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual TSharedPtr<FMonitoredProcess> RunImpl(const TArray<FString>& CommandParams, const FBeamOperationHandle& Op = {}) override;
};
