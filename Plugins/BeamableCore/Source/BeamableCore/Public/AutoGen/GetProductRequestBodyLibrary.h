#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetProductRequestBody.h"

#include "GetProductRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetProductRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetProductRequestBody To JSON String")
	static FString GetProductRequestBodyToJsonString(const UGetProductRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetProductRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetProductRequestBody* Make(FString Sku, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetProductRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetProductRequestBody* Serializable, FString& Sku);
};