#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetPlayerLevelResult.h"

#include "GetPlayerLevelResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetPlayerLevelResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetPlayerLevelResult To JSON String")
	static FString GetPlayerLevelResultToJsonString(const UGetPlayerLevelResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetPlayerLevelResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetPlayerLevelResult* Make(int32 Level, bool bSuccess, int32 TotalXp, int32 XpForCurrentLevel, int32 XpIntoCurrentLevel, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetPlayerLevelResult", meta=(NativeBreakFunc))
	static void Break(const UGetPlayerLevelResult* Serializable, int32& Level, bool& bSuccess, int32& TotalXp, int32& XpForCurrentLevel, int32& XpIntoCurrentLevel, FString& Message);
};