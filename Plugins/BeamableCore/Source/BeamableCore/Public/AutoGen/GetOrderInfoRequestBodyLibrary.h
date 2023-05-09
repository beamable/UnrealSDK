#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetOrderInfoRequestBody.h"

#include "GetOrderInfoRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetOrderInfoRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetOrderInfoRequestBody To JSON String")
	static FString GetOrderInfoRequestBodyToJsonString(const UGetOrderInfoRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetOrderInfoRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetOrderInfoRequestBody* Make(FString OrderId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetOrderInfoRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetOrderInfoRequestBody* Serializable, FString& OrderId);
};