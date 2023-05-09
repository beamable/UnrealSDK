#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsRequestBody.h"

#include "BatchReadStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchReadStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BatchReadStatsRequestBody To JSON String")
	static FString BatchReadStatsRequestBodyToJsonString(const UBatchReadStatsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BatchReadStatsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Stats, Format, Outer", NativeMakeFunc))
	static UBatchReadStatsRequestBody* Make(FBeamStatsType ObjectIds, FOptionalString Stats, FOptionalString Format, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BatchReadStatsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBatchReadStatsRequestBody* Serializable, FBeamStatsType& ObjectIds, FOptionalString& Stats, FOptionalString& Format);
};