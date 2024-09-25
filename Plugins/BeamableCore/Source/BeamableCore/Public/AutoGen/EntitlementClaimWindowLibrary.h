#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/EntitlementClaimWindow.h"

#include "EntitlementClaimWindowLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEntitlementClaimWindowLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EntitlementClaimWindow To JSON String")
	static FString EntitlementClaimWindowToJsonString(const UEntitlementClaimWindow* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EntitlementClaimWindow", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEntitlementClaimWindow* Make(int64 Open, int64 Close, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EntitlementClaimWindow", meta=(NativeBreakFunc))
	static void Break(const UEntitlementClaimWindow* Serializable, int64& Open, int64& Close);
};