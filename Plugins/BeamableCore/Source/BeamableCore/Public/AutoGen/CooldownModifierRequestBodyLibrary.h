#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CooldownModifierRequestBody.h"

#include "CooldownModifierRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCooldownModifierRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="CooldownModifierRequestBody To JSON String")
	static FString CooldownModifierRequestBodyToJsonString(const UCooldownModifierRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make CooldownModifierRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCooldownModifierRequestBody* Make(int64 GamerTag, TArray<UUpdateListingCooldownRequestBody*> UpdateListingCooldownRequests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break CooldownModifierRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCooldownModifierRequestBody* Serializable, int64& GamerTag, TArray<UUpdateListingCooldownRequestBody*>& UpdateListingCooldownRequests);
};