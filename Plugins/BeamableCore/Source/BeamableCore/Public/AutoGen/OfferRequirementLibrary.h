#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OfferRequirement.h"

#include "OfferRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOfferRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="OfferRequirement To JSON String")
	static FString OfferRequirementToJsonString(const UOfferRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make OfferRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOfferRequirement* Make(FString OfferSymbol, UOfferConstraint* Purchases, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break OfferRequirement", meta=(NativeBreakFunc))
	static void Break(const UOfferRequirement* Serializable, FString& OfferSymbol, UOfferConstraint*& Purchases);
};