#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MakeDonationRequestBody.h"

#include "MakeDonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMakeDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MakeDonationRequestBody To JSON String")
	static FString MakeDonationRequestBodyToJsonString(const UMakeDonationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MakeDonationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bAutoClaim, Outer", NativeMakeFunc))
	static UMakeDonationRequestBody* Make(int64 RecipientId, int64 Amount, FOptionalBool bAutoClaim, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MakeDonationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMakeDonationRequestBody* Serializable, int64& RecipientId, int64& Amount, FOptionalBool& bAutoClaim);
};