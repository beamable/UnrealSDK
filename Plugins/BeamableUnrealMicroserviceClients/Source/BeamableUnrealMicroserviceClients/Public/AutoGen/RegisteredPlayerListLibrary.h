#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerList.h"

#include "RegisteredPlayerListLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisteredPlayerListLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisteredPlayerList To JSON String")
	static FString RegisteredPlayerListToJsonString(const URegisteredPlayerList* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisteredPlayerList", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisteredPlayerList* Make(FString Message, TArray<URegisteredPlayer*> Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisteredPlayerList", meta=(NativeBreakFunc))
	static void Break(const URegisteredPlayerList* Serializable, FString& Message, TArray<URegisteredPlayer*>& Players);
};