#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchDeleteInFlightRequestBody.h"

#include "BatchDeleteInFlightRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchDeleteInFlightRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BatchDeleteInFlightRequestBody To JSON String")
	static FString BatchDeleteInFlightRequestBodyToJsonString(const UBatchDeleteInFlightRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BatchDeleteInFlightRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBatchDeleteInFlightRequestBody* Make(TArray<FString> InFlightFailureIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BatchDeleteInFlightRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBatchDeleteInFlightRequestBody* Serializable, TArray<FString>& InFlightFailureIds);
};