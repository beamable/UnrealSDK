#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsRequestArgs.h"

#include "GetGroundItemsRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetGroundItemsRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetGroundItemsRequestArgs To JSON String")
	static FString GetGroundItemsRequestArgsToJsonString(const UGetGroundItemsRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetGroundItemsRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetGroundItemsRequestArgs* Make(FString SpawnerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetGroundItemsRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UGetGroundItemsRequestArgs* Serializable, FString& SpawnerId);
};