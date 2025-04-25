#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetProductRequestBody.h"

#include "GetProductRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetProductRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="GetProductRequestBody To JSON String")
	static FString GetProductRequestBodyToJsonString(const UGetProductRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetProductRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetProductRequestBody* Make(FString Sku, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break GetProductRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetProductRequestBody* Serializable, FString& Sku);
};