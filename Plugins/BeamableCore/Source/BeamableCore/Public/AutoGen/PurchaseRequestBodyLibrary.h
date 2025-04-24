#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PurchaseRequestBody.h"

#include "PurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="PurchaseRequestBody To JSON String")
	static FString PurchaseRequestBodyToJsonString(const UPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPurchaseRequestBody* Make(FString PurchaseId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break PurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPurchaseRequestBody* Serializable, FString& PurchaseId);
};