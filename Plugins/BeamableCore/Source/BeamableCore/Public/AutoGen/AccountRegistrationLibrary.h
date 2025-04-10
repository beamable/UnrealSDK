#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountRegistration.h"

#include "AccountRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AccountRegistration To JSON String")
	static FString AccountRegistrationToJsonString(const UAccountRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AccountRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountRegistration* Make(FString Email, FString Password, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AccountRegistration", meta=(NativeBreakFunc))
	static void Break(const UAccountRegistration* Serializable, FString& Email, FString& Password);
};