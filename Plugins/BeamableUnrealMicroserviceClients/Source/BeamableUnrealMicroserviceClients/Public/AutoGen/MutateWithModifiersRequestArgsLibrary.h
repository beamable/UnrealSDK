#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersRequestArgs.h"

#include "MutateWithModifiersRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMutateWithModifiersRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="MutateWithModifiersRequestArgs To JSON String")
	static FString MutateWithModifiersRequestArgsToJsonString(const UMutateWithModifiersRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make MutateWithModifiersRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMutateWithModifiersRequestArgs* Make(FString PlantItemContentId, int64 PlantItemInstanceId, TArray<FString> ModifierContentIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break MutateWithModifiersRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UMutateWithModifiersRequestArgs* Serializable, FString& PlantItemContentId, int64& PlantItemInstanceId, TArray<FString>& ModifierContentIds);
};