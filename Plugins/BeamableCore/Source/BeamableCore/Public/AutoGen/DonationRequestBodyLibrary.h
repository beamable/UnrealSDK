#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DonationRequestBody.h"

#include "DonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DonationRequestBody To JSON String")
	static FString DonationRequestBodyToJsonString(const UDonationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DonationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDonationRequestBody* Make(bool bSatisfied, int64 TimeRequested, int64 PlayerId, UCurrency* Currency, TArray<UDonationEntry*> Progress, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DonationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDonationRequestBody* Serializable, bool& bSatisfied, int64& TimeRequested, int64& PlayerId, UCurrency*& Currency, TArray<UDonationEntry*>& Progress);
};