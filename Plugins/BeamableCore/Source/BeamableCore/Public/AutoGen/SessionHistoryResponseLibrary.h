#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"

#include "SessionHistoryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionHistoryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionHistoryResponse To JSON String")
	static FString SessionHistoryResponseToJsonString(const USessionHistoryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionHistoryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="InstallDate, Outer", NativeMakeFunc))
	static USessionHistoryResponse* Make(ULocalDate* Date, int32 DaysPlayed, TArray<FString> Payments, TArray<UPaymentTotal*> TotalPaid, TArray<FString> Sessions, FOptionalString InstallDate, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionHistoryResponse", meta=(NativeBreakFunc))
	static void Break(const USessionHistoryResponse* Serializable, ULocalDate*& Date, int32& DaysPlayed, TArray<FString>& Payments, TArray<UPaymentTotal*>& TotalPaid, TArray<FString>& Sessions, FOptionalString& InstallDate);
};