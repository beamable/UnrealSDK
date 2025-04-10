#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MultipliersGetResponse.h"

#include "MultipliersGetResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMultipliersGetResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|4 - Json", DisplayName="MultipliersGetResponse To JSON String")
	static FString MultipliersGetResponseToJsonString(const UMultipliersGetResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Make MultipliersGetResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMultipliersGetResponse* Make(TArray<UVipBonus*> Multipliers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|3 - Backend", DisplayName="Break MultipliersGetResponse", meta=(NativeBreakFunc))
	static void Break(const UMultipliersGetResponse* Serializable, TArray<UVipBonus*>& Multipliers);
};