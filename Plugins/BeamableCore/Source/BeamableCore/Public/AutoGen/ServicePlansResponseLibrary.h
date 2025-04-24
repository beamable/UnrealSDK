#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"

#include "ServicePlansResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlansResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="ServicePlansResponse To JSON String")
	static FString ServicePlansResponseToJsonString(const UServicePlansResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make ServicePlansResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServicePlansResponse* Make(TArray<UServicePlan*> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break ServicePlansResponse", meta=(NativeBreakFunc))
	static void Break(const UServicePlansResponse* Serializable, TArray<UServicePlan*>& Result);
};