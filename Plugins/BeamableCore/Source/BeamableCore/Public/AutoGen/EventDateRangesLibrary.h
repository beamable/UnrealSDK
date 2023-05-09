#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventDateRanges.h"

#include "EventDateRangesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventDateRangesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventDateRanges To JSON String")
	static FString EventDateRangesToJsonString(const UEventDateRanges* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventDateRanges", meta=(DefaultToSelf="Outer", AdvancedDisplay="CreatedAt, Outer", NativeMakeFunc))
	static UEventDateRanges* Make(FString Name, FString State, FString Id, TArray<UDateRange*> Dates, FOptionalInt64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventDateRanges", meta=(NativeBreakFunc))
	static void Break(const UEventDateRanges* Serializable, FString& Name, FString& State, FString& Id, TArray<UDateRange*>& Dates, FOptionalInt64& CreatedAt);
};