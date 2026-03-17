#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"

#include "SessionHistoryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionHistoryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Json", DisplayName="SessionHistoryResponse To JSON String")
	static FString SessionHistoryResponseToJsonString(const USessionHistoryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Make SessionHistoryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Date, InstallDate, DaysPlayed, Sessions, Payments, TotalPaid, Outer", NativeMakeFunc))
	static USessionHistoryResponse* Make(FOptionalString Date, FOptionalString InstallDate, FOptionalInt32 DaysPlayed, FOptionalArrayOfString Sessions, FOptionalArrayOfString Payments, FOptionalArrayOfPlayerSessionActorPaymentTotal TotalPaid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Break SessionHistoryResponse", meta=(NativeBreakFunc))
	static void Break(const USessionHistoryResponse* Serializable, FOptionalString& Date, FOptionalString& InstallDate, FOptionalInt32& DaysPlayed, FOptionalArrayOfString& Sessions, FOptionalArrayOfString& Payments, FOptionalArrayOfPlayerSessionActorPaymentTotal& TotalPaid);
};