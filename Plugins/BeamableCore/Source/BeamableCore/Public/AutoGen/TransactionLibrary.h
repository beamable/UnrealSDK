#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "TransactionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransactionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="Transaction To JSON String")
	static FString TransactionToJsonString(const UTransaction* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make Transaction", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsInTerminalState, State, ProviderId, Created, Updated, Version, ReplayGuardValue, History, Outer", NativeMakeFunc))
	static UTransaction* Make(int64 PlayerId, int64 TransactionId, FString ProviderName, UTransactionDetails* Details, FOptionalBool bIsInTerminalState, FOptionalTransactionState State, FOptionalString ProviderId, FOptionalDateTime Created, FOptionalDateTime Updated, FOptionalString Version, FOptionalString ReplayGuardValue, FOptionalArrayOfTransactionHistoryEntry History, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break Transaction", meta=(NativeBreakFunc))
	static void Break(const UTransaction* Serializable, int64& PlayerId, int64& TransactionId, FString& ProviderName, UTransactionDetails*& Details, FOptionalBool& bIsInTerminalState, FOptionalTransactionState& State, FOptionalString& ProviderId, FOptionalDateTime& Created, FOptionalDateTime& Updated, FOptionalString& Version, FOptionalString& ReplayGuardValue, FOptionalArrayOfTransactionHistoryEntry& History);
};