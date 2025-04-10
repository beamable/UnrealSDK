#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OfferConstraint.h"

#include "OfferConstraintLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOfferConstraintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="OfferConstraint To JSON String")
	static FString OfferConstraintToJsonString(const UOfferConstraint* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make OfferConstraint", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOfferConstraint* Make(FString Constraint, int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break OfferConstraint", meta=(NativeBreakFunc))
	static void Break(const UOfferConstraint* Serializable, FString& Constraint, int32& Value);
};