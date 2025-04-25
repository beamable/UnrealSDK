#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"

#include "PromoteRealmResponseOldLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteRealmResponseOldLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="PromoteRealmResponseOld To JSON String")
	static FString PromoteRealmResponseOldToJsonString(const UPromoteRealmResponseOld* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PromoteRealmResponseOld", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPromoteRealmResponseOld* Make(FString SourcePid, TArray<URealmPromotion*> Promotions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break PromoteRealmResponseOld", meta=(NativeBreakFunc))
	static void Break(const UPromoteRealmResponseOld* Serializable, FString& SourcePid, TArray<URealmPromotion*>& Promotions);
};