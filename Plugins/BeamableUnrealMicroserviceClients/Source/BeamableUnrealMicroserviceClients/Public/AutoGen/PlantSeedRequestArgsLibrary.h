#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantSeedRequestArgs.h"

#include "PlantSeedRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPlantSeedRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="PlantSeedRequestArgs To JSON String")
	static FString PlantSeedRequestArgsToJsonString(const UPlantSeedRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make PlantSeedRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPlantSeedRequestArgs* Make(FString SeedContentId, FString SlotId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break PlantSeedRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UPlantSeedRequestArgs* Serializable, FString& SeedContentId, FString& SlotId);
};