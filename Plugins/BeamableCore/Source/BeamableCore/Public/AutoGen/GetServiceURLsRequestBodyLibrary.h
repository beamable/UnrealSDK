#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetServiceURLsRequestBody.h"

#include "GetServiceURLsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetServiceURLsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetServiceURLsRequestBody To JSON String")
	static FString GetServiceURLsRequestBodyToJsonString(const UGetServiceURLsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetServiceURLsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetServiceURLsRequestBody* Make(TArray<UServiceImageLayers*> Requests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetServiceURLsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetServiceURLsRequestBody* Serializable, TArray<UServiceImageLayers*>& Requests);
};