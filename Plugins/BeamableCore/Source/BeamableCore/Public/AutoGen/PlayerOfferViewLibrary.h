#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerOfferView.h"

#include "PlayerOfferViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerOfferViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="PlayerOfferView To JSON String")
	static FString PlayerOfferViewToJsonString(const UPlayerOfferView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PlayerOfferView", meta=(DefaultToSelf="Outer", AdvancedDisplay="ButtonText, Outer", NativeMakeFunc))
	static UPlayerOfferView* Make(int32 Coupons, UPrice* Price, FString Symbol, TArray<FString> Titles, TArray<UItemCreateRequestBody*> ObtainItems, TArray<UCurrencyChange*> ObtainCurrency, TArray<FString> Images, TArray<FString> Descriptions, TArray<FString> Obtain, FOptionalString ButtonText, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break PlayerOfferView", meta=(NativeBreakFunc))
	static void Break(const UPlayerOfferView* Serializable, int32& Coupons, UPrice*& Price, FString& Symbol, TArray<FString>& Titles, TArray<UItemCreateRequestBody*>& ObtainItems, TArray<UCurrencyChange*>& ObtainCurrency, TArray<FString>& Images, TArray<FString>& Descriptions, TArray<FString>& Obtain, FOptionalString& ButtonText);
};