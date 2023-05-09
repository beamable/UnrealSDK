#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyPreview.h"

#include "CurrencyPreviewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyPreviewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CurrencyPreview To JSON String")
	static FString CurrencyPreviewToJsonString(const UCurrencyPreview* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CurrencyPreview", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCurrencyPreview* Make(FString Id, int64 Amount, int64 OriginalAmount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CurrencyPreview", meta=(NativeBreakFunc))
	static void Break(const UCurrencyPreview* Serializable, FString& Id, int64& Amount, int64& OriginalAmount);
};