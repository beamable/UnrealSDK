#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventDateRanges.h"

#include "EventDateRangesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventDateRangesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventDateRanges To JSON String")
	static FString EventDateRangesToJsonString(const UEventDateRanges* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventDateRanges", meta=(DefaultToSelf="Outer", AdvancedDisplay="CreatedAt, Outer", NativeMakeFunc))
	static UEventDateRanges* Make(FString Name, FString State, FString Id, TArray<UDateRange*> Dates, FOptionalInt64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventDateRanges", meta=(NativeBreakFunc))
	static void Break(const UEventDateRanges* Serializable, FString& Name, FString& State, FString& Id, TArray<UDateRange*>& Dates, FOptionalInt64& CreatedAt);
};