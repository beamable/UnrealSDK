#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponse.h"

#include "BatchReadStatsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchReadStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="BatchReadStatsResponse To JSON String")
	static FString BatchReadStatsResponseToJsonString(const UBatchReadStatsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make BatchReadStatsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBatchReadStatsResponse* Make(TArray<UNetworkSerializable*> Results, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break BatchReadStatsResponse", meta=(NativeBreakFunc))
	static void Break(const UBatchReadStatsResponse* Serializable, TArray<UNetworkSerializable*>& Results);
};