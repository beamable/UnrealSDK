#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayer.h"

#include "RegisteredPlayerLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisteredPlayerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisteredPlayer To JSON String")
	static FString RegisteredPlayerToJsonString(const URegisteredPlayer* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisteredPlayer", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisteredPlayer* Make(int64 PlayerId, int32 DeviceCount, int64 LastUpdated, FString GamePlatform, FString GameDevice, TArray<FString> Platforms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisteredPlayer", meta=(NativeBreakFunc))
	static void Break(const URegisteredPlayer* Serializable, int64& PlayerId, int32& DeviceCount, int64& LastUpdated, FString& GamePlatform, FString& GameDevice, TArray<FString>& Platforms);
};