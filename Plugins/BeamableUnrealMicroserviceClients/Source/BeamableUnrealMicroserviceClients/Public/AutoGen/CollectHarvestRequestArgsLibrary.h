#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectHarvestRequestArgs.h"

#include "CollectHarvestRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectHarvestRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="CollectHarvestRequestArgs To JSON String")
	static FString CollectHarvestRequestArgsToJsonString(const UCollectHarvestRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make CollectHarvestRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCollectHarvestRequestArgs* Make(FString SlotId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break CollectHarvestRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UCollectHarvestRequestArgs* Serializable, FString& SlotId);
};