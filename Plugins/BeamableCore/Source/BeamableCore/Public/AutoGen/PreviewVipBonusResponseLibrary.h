#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PreviewVipBonusResponse.h"

#include "PreviewVipBonusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPreviewVipBonusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="PreviewVipBonusResponse To JSON String")
	static FString PreviewVipBonusResponseToJsonString(const UPreviewVipBonusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PreviewVipBonusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPreviewVipBonusResponse* Make(TArray<UCurrencyPreview*> Currencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break PreviewVipBonusResponse", meta=(NativeBreakFunc))
	static void Break(const UPreviewVipBonusResponse* Serializable, TArray<UCurrencyPreview*>& Currencies);
};