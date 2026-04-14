#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlansResponse.h"

#include "RealmsBasicServicePlansResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicServicePlansResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicServicePlansResponse To JSON String")
	static FString RealmsBasicServicePlansResponseToJsonString(const URealmsBasicServicePlansResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicServicePlansResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicServicePlansResponse* Make(TArray<URealmsBasicServicePlan*> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicServicePlansResponse", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicServicePlansResponse* Serializable, TArray<URealmsBasicServicePlan*>& Result);
};