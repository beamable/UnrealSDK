#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GroundItemEntry.h"

#include "GroundItemEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGroundItemEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GroundItemEntry To JSON String")
	static FString GroundItemEntryToJsonString(const UGroundItemEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GroundItemEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroundItemEntry* Make(FString GroundItemId, FString ContentId, int32 Quantity, FString ItemType, float PosX, float PosY, float PosZ, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GroundItemEntry", meta=(NativeBreakFunc))
	static void Break(const UGroundItemEntry* Serializable, FString& GroundItemId, FString& ContentId, int32& Quantity, FString& ItemType, float& PosX, float& PosY, float& PosZ);
};