#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateRequestArgs.h"

#include "MutateRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMutateRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="MutateRequestArgs To JSON String")
	static FString MutateRequestArgsToJsonString(const UMutateRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make MutateRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMutateRequestArgs* Make(TArray<UMutationInput*> Inputs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break MutateRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UMutateRequestArgs* Serializable, TArray<UMutationInput*>& Inputs);
};