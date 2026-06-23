#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantResult.h"

#include "PlantResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPlantResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="PlantResult To JSON String")
	static FString PlantResultToJsonString(const UPlantResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make PlantResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPlantResult* Make(bool bSuccess, int64 PlantedAtUtcSeconds, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break PlantResult", meta=(NativeBreakFunc))
	static void Break(const UPlantResult* Serializable, bool& bSuccess, int64& PlantedAtUtcSeconds, FString& Message);
};