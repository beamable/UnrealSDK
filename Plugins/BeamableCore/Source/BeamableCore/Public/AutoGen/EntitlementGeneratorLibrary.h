#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EntitlementGenerator.h"

#include "EntitlementGeneratorLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEntitlementGeneratorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="EntitlementGenerator To JSON String")
	static FString EntitlementGeneratorToJsonString(const UEntitlementGenerator* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make EntitlementGenerator", meta=(DefaultToSelf="Outer", AdvancedDisplay="Quantity, ClaimWindow, Specialization, Params, Outer", NativeMakeFunc))
	static UEntitlementGenerator* Make(FString Symbol, FString Action, FOptionalInt32 Quantity, FOptionalEntitlementClaimWindow ClaimWindow, FOptionalString Specialization, FOptionalMapOfString Params, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break EntitlementGenerator", meta=(NativeBreakFunc))
	static void Break(const UEntitlementGenerator* Serializable, FString& Symbol, FString& Action, FOptionalInt32& Quantity, FOptionalEntitlementClaimWindow& ClaimWindow, FOptionalString& Specialization, FOptionalMapOfString& Params);
};