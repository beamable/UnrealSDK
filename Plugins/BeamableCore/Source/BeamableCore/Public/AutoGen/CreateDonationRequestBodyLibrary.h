#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateDonationRequestBody.h"

#include "CreateDonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateDonationRequestBody To JSON String")
	static FString CreateDonationRequestBodyToJsonString(const UCreateDonationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateDonationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Config, Outer", NativeMakeFunc))
	static UCreateDonationRequestBody* Make(FString CurrencyId, int64 Amount, FOptionalString Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateDonationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateDonationRequestBody* Serializable, FString& CurrencyId, int64& Amount, FOptionalString& Config);
};