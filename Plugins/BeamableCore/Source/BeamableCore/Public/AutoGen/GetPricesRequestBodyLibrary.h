#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetPricesRequestBody.h"

#include "GetPricesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetPricesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="GetPricesRequestBody To JSON String")
	static FString GetPricesRequestBodyToJsonString(const UGetPricesRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetPricesRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetPricesRequestBody* Make(int64 SteamId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break GetPricesRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetPricesRequestBody* Serializable, int64& SteamId);
};