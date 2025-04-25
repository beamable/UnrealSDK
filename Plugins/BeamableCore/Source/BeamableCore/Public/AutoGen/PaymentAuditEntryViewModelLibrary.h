#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentAuditEntryViewModel.h"

#include "PaymentAuditEntryViewModelLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentAuditEntryViewModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="PaymentAuditEntryViewModel To JSON String")
	static FString PaymentAuditEntryViewModelToJsonString(const UPaymentAuditEntryViewModel* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PaymentAuditEntryViewModel", meta=(DefaultToSelf="Outer", AdvancedDisplay="Version, Updated, ReplayGuardValue, Created, ObtainItems, ObtainCurrency, Outer", NativeMakeFunc))
	static UPaymentAuditEntryViewModel* Make(FString Providerid, int64 Txid, FString Providername, FString Txstate, UPaymentDetailsEntryViewModel* Details, int64 Gt, TArray<UPaymentHistoryEntryViewModel*> History, TArray<UEntitlementGenerator*> Entitlements, FOptionalString Version, FOptionalInt64 Updated, FOptionalString ReplayGuardValue, FOptionalInt64 Created, FOptionalArrayOfItemCreateRequestBody ObtainItems, FOptionalArrayOfCurrencyChange ObtainCurrency, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break PaymentAuditEntryViewModel", meta=(NativeBreakFunc))
	static void Break(const UPaymentAuditEntryViewModel* Serializable, FString& Providerid, int64& Txid, FString& Providername, FString& Txstate, UPaymentDetailsEntryViewModel*& Details, int64& Gt, TArray<UPaymentHistoryEntryViewModel*>& History, TArray<UEntitlementGenerator*>& Entitlements, FOptionalString& Version, FOptionalInt64& Updated, FOptionalString& ReplayGuardValue, FOptionalInt64& Created, FOptionalArrayOfItemCreateRequestBody& ObtainItems, FOptionalArrayOfCurrencyChange& ObtainCurrency);
};