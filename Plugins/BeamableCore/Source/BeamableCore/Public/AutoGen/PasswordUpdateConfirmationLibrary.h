#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PasswordUpdateConfirmation.h"

#include "PasswordUpdateConfirmationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPasswordUpdateConfirmationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="PasswordUpdateConfirmation To JSON String")
	static FString PasswordUpdateConfirmationToJsonString(const UPasswordUpdateConfirmation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PasswordUpdateConfirmation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, Outer", NativeMakeFunc))
	static UPasswordUpdateConfirmation* Make(FString Code, FString NewPassword, FOptionalString Email, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break PasswordUpdateConfirmation", meta=(NativeBreakFunc))
	static void Break(const UPasswordUpdateConfirmation* Serializable, FString& Code, FString& NewPassword, FOptionalString& Email);
};