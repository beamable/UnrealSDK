#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"

#include "ServicePlansResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlansResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServicePlansResponse To JSON String")
	static FString ServicePlansResponseToJsonString(const UServicePlansResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServicePlansResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServicePlansResponse* Make(TArray<UServicePlan*> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServicePlansResponse", meta=(NativeBreakFunc))
	static void Break(const UServicePlansResponse* Serializable, TArray<UServicePlan*>& Result);
};