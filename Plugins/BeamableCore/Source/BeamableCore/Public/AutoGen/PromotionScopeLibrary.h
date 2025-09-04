#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromotionScope.h"

#include "PromotionScopeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromotionScopeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="PromotionScope To JSON String")
	static FString PromotionScopeToJsonString(const UPromotionScope* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PromotionScope", meta=(DefaultToSelf="Outer", AdvancedDisplay="Promotions, Outer", NativeMakeFunc))
	static UPromotionScope* Make(EBeamPromotableType Name, FOptionalArrayOfPromotion Promotions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break PromotionScope", meta=(NativeBreakFunc))
	static void Break(const UPromotionScope* Serializable, EBeamPromotableType& Name, FOptionalArrayOfPromotion& Promotions);
};