#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SlotStateEntry.h"

#include "SlotStateEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USlotStateEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SlotStateEntry To JSON String")
	static FString SlotStateEntryToJsonString(const USlotStateEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SlotStateEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USlotStateEntry* Make(FString SlotId, FString SeedId, FString HarvestId, int64 PlantedAt, int32 GrowSecs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SlotStateEntry", meta=(NativeBreakFunc))
	static void Break(const USlotStateEntry* Serializable, FString& SlotId, FString& SeedId, FString& HarvestId, int64& PlantedAt, int32& GrowSecs);
};