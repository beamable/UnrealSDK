#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TransactionHistoryEntry.h"

#include "TransactionHistoryEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransactionHistoryEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="TransactionHistoryEntry To JSON String")
	static FString TransactionHistoryEntryToJsonString(const UTransactionHistoryEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make TransactionHistoryEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Data, Outer", NativeMakeFunc))
	static UTransactionHistoryEntry* Make(EBeamTransactionState Change, FDateTime Timestamp, FOptionalString Data, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break TransactionHistoryEntry", meta=(NativeBreakFunc))
	static void Break(const UTransactionHistoryEntry* Serializable, EBeamTransactionState& Change, FDateTime& Timestamp, FOptionalString& Data);
};