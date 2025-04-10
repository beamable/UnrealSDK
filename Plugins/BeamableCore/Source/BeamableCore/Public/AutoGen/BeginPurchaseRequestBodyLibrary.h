#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBody.h"

#include "BeginPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeginPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|4 - Json", DisplayName="BeginPurchaseRequestBody To JSON String")
	static FString BeginPurchaseRequestBodyToJsonString(const UBeginPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Make BeginPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Language, Time, Outer", NativeMakeFunc))
	static UBeginPurchaseRequestBody* Make(FString PurchaseId, FOptionalString Language, FOptionalString Time, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Break BeginPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeginPurchaseRequestBody* Serializable, FString& PurchaseId, FOptionalString& Language, FOptionalString& Time);
};