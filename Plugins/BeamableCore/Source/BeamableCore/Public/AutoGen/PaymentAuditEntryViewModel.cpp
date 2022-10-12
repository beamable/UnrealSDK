
#include "AutoGen/PaymentAuditEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UPaymentAuditEntryViewModel ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerid"), Providerid);
	UBeamJsonUtils::SerializeArray<UPaymentHistoryEntryViewModel*>(TEXT("history"), History, Serializer);
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("providername"), Providername);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	Serializer->WriteValue(TEXT("txstate"), Txstate);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("entitlements"), Entitlements, Serializer);
	UBeamJsonUtils::SerializeUObject<UPaymentDetailsEntryViewModel*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);
}

void UPaymentAuditEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerid"), Providerid);
	UBeamJsonUtils::SerializeArray<UPaymentHistoryEntryViewModel*>(TEXT("history"), History, Serializer);
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("providername"), Providername);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("obtainItems"), &ObtainItems, Serializer);
	Serializer->WriteValue(TEXT("txstate"), Txstate);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updated"), &Updated, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>(TEXT("obtainCurrency"), &ObtainCurrency, Serializer);
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("entitlements"), Entitlements, Serializer);
	UBeamJsonUtils::SerializeUObject<UPaymentDetailsEntryViewModel*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("replayGuardValue"), &ReplayGuardValue, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("created"), &Created, Serializer);		
}

void UPaymentAuditEntryViewModel ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Providerid = Bag->GetStringField(TEXT("providerid"));
	UBeamJsonUtils::DeserializeArray<UPaymentHistoryEntryViewModel*>(Bag->GetArrayField(TEXT("history")), History, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("txid")), Txid);
	Providername = Bag->GetStringField(TEXT("providername"));
	UBeamJsonUtils::DeserializeOptional<FString>("version", Bag, Version, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("obtainItems", Bag, ObtainItems, OuterOwner);
	Txstate = Bag->GetStringField(TEXT("txstate"));
	UBeamJsonUtils::DeserializeOptional<int64>("updated", Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyChange*>, UCurrencyChange*>("obtainCurrency", Bag, ObtainCurrency, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEntitlementGenerator*>(Bag->GetArrayField(TEXT("entitlements")), Entitlements, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UPaymentDetailsEntryViewModel*>("details", Bag, Details, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("replayGuardValue", Bag, ReplayGuardValue, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
	UBeamJsonUtils::DeserializeOptional<int64>("created", Bag, Created, OuterOwner);
}