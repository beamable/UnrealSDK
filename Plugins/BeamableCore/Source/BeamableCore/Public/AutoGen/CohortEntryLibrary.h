#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CohortEntry.h"

#include "CohortEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCohortEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="CohortEntry To JSON String")
	static FString CohortEntryToJsonString(const UCohortEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make CohortEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCohortEntry* Make(FString Trial, FString Cohort, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break CohortEntry", meta=(NativeBreakFunc))
	static void Break(const UCohortEntry* Serializable, FString& Trial, FString& Cohort);
};