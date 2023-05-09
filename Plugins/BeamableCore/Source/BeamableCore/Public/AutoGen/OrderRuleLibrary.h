#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OrderRule.h"

#include "OrderRuleLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOrderRuleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - OrderRule To JSON String")
	static FString OrderRuleToJsonString(const UOrderRule* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make OrderRule", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOrderRule* Make(FString V, int32 O, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break OrderRule", meta=(NativeBreakFunc))
	static void Break(const UOrderRule* Serializable, FString& V, int32& O);
};