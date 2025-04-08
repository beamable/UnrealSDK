#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponse.h"

#include "BatchReadStatsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchReadStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="BatchReadStatsResponse To JSON String")
	static FString BatchReadStatsResponseToJsonString(const UBatchReadStatsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make BatchReadStatsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBatchReadStatsResponse* Make(TArray<UNetworkSerializable*> Results, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break BatchReadStatsResponse", meta=(NativeBreakFunc))
	static void Break(const UBatchReadStatsResponse* Serializable, TArray<UNetworkSerializable*>& Results);
};