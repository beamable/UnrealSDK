#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OrderRules.h"

#include "OrderRulesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOrderRulesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - OrderRules To JSON String")
	static FString OrderRulesToJsonString(const UOrderRules* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make OrderRules", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOrderRules* Make(TArray<UOrderRule*> Orules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break OrderRules", meta=(NativeBreakFunc))
	static void Break(const UOrderRules* Serializable, TArray<UOrderRule*>& Orules);
};