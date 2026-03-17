#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerSessionActorPaymentTotal.h"

#include "PlayerSessionActorPaymentTotalLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerSessionActorPaymentTotalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Json", DisplayName="PlayerSessionActorPaymentTotal To JSON String")
	static FString PlayerSessionActorPaymentTotalToJsonString(const UPlayerSessionActorPaymentTotal* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Make PlayerSessionActorPaymentTotal", meta=(DefaultToSelf="Outer", AdvancedDisplay="Currency, Amount, Outer", NativeMakeFunc))
	static UPlayerSessionActorPaymentTotal* Make(FOptionalString Currency, FOptionalInt64 Amount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerSession|Utils|Make/Break", DisplayName="Break PlayerSessionActorPaymentTotal", meta=(NativeBreakFunc))
	static void Break(const UPlayerSessionActorPaymentTotal* Serializable, FOptionalString& Currency, FOptionalInt64& Amount);
};