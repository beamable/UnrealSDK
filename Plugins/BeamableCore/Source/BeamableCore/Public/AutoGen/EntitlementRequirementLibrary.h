#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EntitlementRequirement.h"

#include "EntitlementRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEntitlementRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EntitlementRequirement To JSON String")
	static FString EntitlementRequirementToJsonString(const UEntitlementRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EntitlementRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Specialization, Outer", NativeMakeFunc))
	static UEntitlementRequirement* Make(FString Symbol, FString Constraint, FString State, FOptionalString Specialization, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EntitlementRequirement", meta=(NativeBreakFunc))
	static void Break(const UEntitlementRequirement* Serializable, FString& Symbol, FString& Constraint, FString& State, FOptionalString& Specialization);
};