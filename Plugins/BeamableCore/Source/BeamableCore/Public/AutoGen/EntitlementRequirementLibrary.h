#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EntitlementRequirement.h"

#include "EntitlementRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEntitlementRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="EntitlementRequirement To JSON String")
	static FString EntitlementRequirementToJsonString(const UEntitlementRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make EntitlementRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Specialization, Outer", NativeMakeFunc))
	static UEntitlementRequirement* Make(FString Symbol, FString Constraint, FString State, FOptionalString Specialization, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break EntitlementRequirement", meta=(NativeBreakFunc))
	static void Break(const UEntitlementRequirement* Serializable, FString& Symbol, FString& Constraint, FString& State, FOptionalString& Specialization);
};