
#include "BeamableCore/Public/AutoGen/Transaction.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UTransaction::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTransaction::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transactionId"), TransactionId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerName"), ProviderName, Serializer);
	UBeamJsonUtils::SerializeUObject<UTransactionDetails*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isInTerminalState"), &bIsInTerminalState, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamTransactionState>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerId"), &ProviderId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTransactionHistoryEntry*>, UTransactionHistoryEntry*>(TEXT("history"), &History, Serializer);
}

void UTransaction::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transactionId"), TransactionId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerName"), ProviderName, Serializer);
	UBeamJsonUtils::SerializeUObject<UTransactionDetails*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isInTerminalState"), &bIsInTerminalState, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamTransactionState>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerId"), &ProviderId, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTransactionHistoryEntry*>, UTransactionHistoryEntry*>(TEXT("history"), &History, Serializer);		
}

void UTransaction::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("transactionId"), Bag, TransactionId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("providerName"), Bag, ProviderName);
	UBeamJsonUtils::DeserializeUObject<UTransactionDetails*>("details", Bag, Details, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("isInTerminalState", Bag, bIsInTerminalState, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamTransactionState>("state", Bag, State, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("providerId", Bag, ProviderId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("updated", Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("version", Bag, Version, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("replayGuardValue", Bag, ReplayGuardValue, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTransactionHistoryEntry*>, UTransactionHistoryEntry*>("history", Bag, History, OuterOwner);
}



