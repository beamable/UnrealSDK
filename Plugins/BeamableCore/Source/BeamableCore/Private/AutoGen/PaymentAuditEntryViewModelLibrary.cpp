
#include "BeamableCore/Public/AutoGen/PaymentAuditEntryViewModelLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentAuditEntryViewModelLibrary::PaymentAuditEntryViewModelToJsonString(const UPaymentAuditEntryViewModel* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UPaymentAuditEntryViewModel* UPaymentAuditEntryViewModelLibrary::Make(FString Providerid, int64 Txid, FString Providername, FString Txstate, UPaymentDetailsEntryViewModel* Details, int64 Gt, TArray<UPaymentHistoryEntryViewModel*> History, TArray<UEntitlementGenerator*> Entitlements, FOptionalString Version, FOptionalInt64 Updated, FOptionalString ReplayGuardValue, FOptionalInt64 Created, FOptionalArrayOfItemCreateRequestBody ObtainItems, FOptionalArrayOfCurrencyChange ObtainCurrency, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentAuditEntryViewModel>(Outer);
	Serializable->Providerid = Providerid;
	Serializable->Txid = Txid;
	Serializable->Providername = Providername;
	Serializable->Txstate = Txstate;
	Serializable->Details = Details;
	Serializable->Gt = Gt;
	Serializable->History = History;
	Serializable->Entitlements = Entitlements;
	Serializable->Version = Version;
	Serializable->Updated = Updated;
	Serializable->ReplayGuardValue = ReplayGuardValue;
	Serializable->Created = Created;
	Serializable->ObtainItems = ObtainItems;
	Serializable->ObtainCurrency = ObtainCurrency;
	
	return Serializable;
}

void UPaymentAuditEntryViewModelLibrary::Break(const UPaymentAuditEntryViewModel* Serializable, FString& Providerid, int64& Txid, FString& Providername, FString& Txstate, UPaymentDetailsEntryViewModel*& Details, int64& Gt, TArray<UPaymentHistoryEntryViewModel*>& History, TArray<UEntitlementGenerator*>& Entitlements, FOptionalString& Version, FOptionalInt64& Updated, FOptionalString& ReplayGuardValue, FOptionalInt64& Created, FOptionalArrayOfItemCreateRequestBody& ObtainItems, FOptionalArrayOfCurrencyChange& ObtainCurrency)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Providerid = Serializable->Providerid;
		Txid = Serializable->Txid;
		Providername = Serializable->Providername;
		Txstate = Serializable->Txstate;
		Details = Serializable->Details;
		Gt = Serializable->Gt;
		History = Serializable->History;
		Entitlements = Serializable->Entitlements;
		Version = Serializable->Version;
		Updated = Serializable->Updated;
		ReplayGuardValue = Serializable->ReplayGuardValue;
		Created = Serializable->Created;
		ObtainItems = Serializable->ObtainItems;
		ObtainCurrency = Serializable->ObtainCurrency;
	}
		
}

