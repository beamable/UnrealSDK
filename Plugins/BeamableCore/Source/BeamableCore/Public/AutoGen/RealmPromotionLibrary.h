#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmPromotion.h"

#include "RealmPromotionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmPromotionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmPromotion To JSON String")
	static FString RealmPromotionToJsonString(const URealmPromotion* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmPromotion", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmPromotion* Make(FString Name, UPromotable* Source, UPromotable* Destination, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmPromotion", meta=(NativeBreakFunc))
	static void Break(const URealmPromotion* Serializable, FString& Name, UPromotable*& Source, UPromotable*& Destination);
};