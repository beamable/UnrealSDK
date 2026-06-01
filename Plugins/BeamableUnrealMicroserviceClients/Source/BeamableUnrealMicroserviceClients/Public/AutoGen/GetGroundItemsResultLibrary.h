#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsResult.h"

#include "GetGroundItemsResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetGroundItemsResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetGroundItemsResult To JSON String")
	static FString GetGroundItemsResultToJsonString(const UGetGroundItemsResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetGroundItemsResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetGroundItemsResult* Make(bool bSuccess, FString Message, TArray<UGroundItemEntry*> Items, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetGroundItemsResult", meta=(NativeBreakFunc))
	static void Break(const UGetGroundItemsResult* Serializable, bool& bSuccess, FString& Message, TArray<UGroundItemEntry*>& Items);
};