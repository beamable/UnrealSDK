#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsRequestBody.h"

#include "BatchReadStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchReadStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="BatchReadStatsRequestBody To JSON String")
	static FString BatchReadStatsRequestBodyToJsonString(const UBatchReadStatsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make BatchReadStatsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Stats, Format, Outer", NativeMakeFunc))
	static UBatchReadStatsRequestBody* Make(FBeamStatsType ObjectIds, FOptionalString Stats, FOptionalString Format, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break BatchReadStatsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBatchReadStatsRequestBody* Serializable, FBeamStatsType& ObjectIds, FOptionalString& Stats, FOptionalString& Format);
};