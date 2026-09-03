#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesResult.h"

#include "GetSlotStatesResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetSlotStatesResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetSlotStatesResult To JSON String")
	static FString GetSlotStatesResultToJsonString(const UGetSlotStatesResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetSlotStatesResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSlotStatesResult* Make(bool bSuccess, FString Message, TArray<USlotStateEntry*> Slots, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetSlotStatesResult", meta=(NativeBreakFunc))
	static void Break(const UGetSlotStatesResult* Serializable, bool& bSuccess, FString& Message, TArray<USlotStateEntry*>& Slots);
};