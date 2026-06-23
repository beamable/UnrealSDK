#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersResult.h"

#include "MutateWithModifiersResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMutateWithModifiersResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="MutateWithModifiersResult To JSON String")
	static FString MutateWithModifiersResultToJsonString(const UMutateWithModifiersResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make MutateWithModifiersResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMutateWithModifiersResult* Make(bool bSuccess, FString Message, TMap<FString, FString> NewProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break MutateWithModifiersResult", meta=(NativeBreakFunc))
	static void Break(const UMutateWithModifiersResult* Serializable, bool& bSuccess, FString& Message, TMap<FString, FString>& NewProperties);
};