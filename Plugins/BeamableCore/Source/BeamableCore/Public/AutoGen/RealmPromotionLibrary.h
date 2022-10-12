
#pragma once

#include "CoreMinimal.h"
#include "RealmPromotion.h"

#include "RealmPromotionLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URealmPromotionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RealmPromotion To JSON String")
	static FString RealmPromotionToJsonString(const URealmPromotion* Serializable, const bool Pretty);		
};