#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesRequestArgs.h"

#include "GetSlotStatesRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetSlotStatesRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetSlotStatesRequestArgs To JSON String")
	static FString GetSlotStatesRequestArgsToJsonString(const UGetSlotStatesRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetSlotStatesRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSlotStatesRequestArgs* Make(TArray<FString> SlotIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetSlotStatesRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UGetSlotStatesRequestArgs* Serializable, TArray<FString>& SlotIds);
};