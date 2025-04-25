#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CohortRequirement.h"

#include "CohortRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCohortRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="CohortRequirement To JSON String")
	static FString CohortRequirementToJsonString(const UCohortRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make CohortRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCohortRequirement* Make(FString Trial, FString Cohort, FString Constraint, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break CohortRequirement", meta=(NativeBreakFunc))
	static void Break(const UCohortRequirement* Serializable, FString& Trial, FString& Cohort, FString& Constraint);
};