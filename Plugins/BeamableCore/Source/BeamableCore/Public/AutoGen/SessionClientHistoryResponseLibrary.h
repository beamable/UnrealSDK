#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#include "SessionClientHistoryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionClientHistoryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SessionClientHistoryResponse To JSON String")
	static FString SessionClientHistoryResponseToJsonString(const USessionClientHistoryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SessionClientHistoryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="InstallDate, Outer", NativeMakeFunc))
	static USessionClientHistoryResponse* Make(ULocalDate* Date, int32 DaysPlayed, TArray<FString> Sessions, FOptionalString InstallDate, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SessionClientHistoryResponse", meta=(NativeBreakFunc))
	static void Break(const USessionClientHistoryResponse* Serializable, ULocalDate*& Date, int32& DaysPlayed, TArray<FString>& Sessions, FOptionalString& InstallDate);
};