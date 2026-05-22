#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationResult.h"

#include "MutationResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMutationResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="MutationResult To JSON String")
	static FString MutationResultToJsonString(const UMutationResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make MutationResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMutationResult* Make(bool bSuccess, FString Message, TArray<UMutationOutput*> Outputs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break MutationResult", meta=(NativeBreakFunc))
	static void Break(const UMutationResult* Serializable, bool& bSuccess, FString& Message, TArray<UMutationOutput*>& Outputs);
};