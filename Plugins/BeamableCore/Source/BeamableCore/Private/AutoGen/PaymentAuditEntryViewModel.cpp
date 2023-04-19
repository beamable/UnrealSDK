
#include "BeamableCore/Public/AutoGen/PaymentAuditEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPaymentAuditEntryViewModel::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerid"), Providerid);
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("providername"), Providername);
	Serializer->WriteValue(TEXT("txstate"), Txstate);
	UBeamJsonUtils::SerializeUObject<UPaymentDetailsEntryViewModel*>("details", Details, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeArray<UPaymentHistoryEntryViewModel*>(TEXT("history"), History, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("entitlements"), Entitlements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);
}

void UPaymentAuditEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerid"), Providerid);
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("providername"), Providername);
	Serializer->WriteValue(TEXT("txstate"), Txstate);
	UBeamJsonUtils::SerializeUObject<UPaymentDetailsEntryViewModel*>("details", Details, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeArray<UPaymentHistoryEntryViewModel*>(TEXT("history"), History, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("entitlements"), Entitlements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);		
}

void UPaymentAuditEntryViewModel::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Providerid = Bag->GetStringField(TEXT("providerid"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("txid")), Txid);
	Providername = Bag->GetStringField(TEXT("providername"));
	Txstate = Bag->GetStringField(TEXT("txstate"));
	UBeamJsonUtils::DeserializeUObject<UPaymentDetailsEntryViewModel*>("details", Bag, Details, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
	UBeamJsonUtils::DeserializeArray<UPaymentHistoryEntryViewModel*>(Bag->GetArrayField(TEXT("history")), History, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEntitlementGenerator*>(Bag->GetArrayField(TEXT("entitlements")), Entitlements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("version", Bag, Version, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updated", Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("replayGuardValue", Bag, ReplayGuardValue, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("obtainItems", Bag, ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>("obtainCurrency", Bag, ObtainCurrency, OuterOwner);
}



