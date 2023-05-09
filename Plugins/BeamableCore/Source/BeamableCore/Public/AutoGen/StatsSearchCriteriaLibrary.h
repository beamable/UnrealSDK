#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatsSearchCriteria.h"

#include "StatsSearchCriteriaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatsSearchCriteriaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatsSearchCriteria To JSON String")
	static FString StatsSearchCriteriaToJsonString(const UStatsSearchCriteria* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatsSearchCriteria", meta=(DefaultToSelf="Outer", AdvancedDisplay="Value, Outer", NativeMakeFunc))
	static UStatsSearchCriteria* Make(FString Stat, FString Rel, FOptionalString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatsSearchCriteria", meta=(NativeBreakFunc))
	static void Break(const UStatsSearchCriteria* Serializable, FString& Stat, FString& Rel, FOptionalString& Value);
};