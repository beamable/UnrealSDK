#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#include "SessionClientHistoryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionClientHistoryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Json", DisplayName="SessionClientHistoryResponse To JSON String")
	static FString SessionClientHistoryResponseToJsonString(const USessionClientHistoryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Make SessionClientHistoryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Date, InstallDate, DaysPlayed, Sessions, Outer", NativeMakeFunc))
	static USessionClientHistoryResponse* Make(FOptionalString Date, FOptionalString InstallDate, FOptionalInt32 DaysPlayed, FOptionalArrayOfString Sessions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Break SessionClientHistoryResponse", meta=(NativeBreakFunc))
	static void Break(const USessionClientHistoryResponse* Serializable, FOptionalString& Date, FOptionalString& InstallDate, FOptionalInt32& DaysPlayed, FOptionalArrayOfString& Sessions);
};