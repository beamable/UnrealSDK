#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBody.h"

#include "TrackPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTrackPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="TrackPurchaseRequestBody To JSON String")
	static FString TrackPurchaseRequestBodyToJsonString(const UTrackPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make TrackPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTrackPurchaseRequestBody* Make(double PriceInLocalCurrency, FString SkuName, FString SkuProductId, FString Store, FString PurchaseId, FString IsoCurrencySymbol, TArray<UItemCreateRequestBody*> ObtainItems, TArray<UCurrencyChange*> ObtainCurrency, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break TrackPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTrackPurchaseRequestBody* Serializable, double& PriceInLocalCurrency, FString& SkuName, FString& SkuProductId, FString& Store, FString& PurchaseId, FString& IsoCurrencySymbol, TArray<UItemCreateRequestBody*>& ObtainItems, TArray<UCurrencyChange*>& ObtainCurrency);
};