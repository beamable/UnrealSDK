#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmailUpdateConfirmation.h"

#include "EmailUpdateConfirmationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmailUpdateConfirmationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EmailUpdateConfirmation To JSON String")
	static FString EmailUpdateConfirmationToJsonString(const UEmailUpdateConfirmation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EmailUpdateConfirmation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEmailUpdateConfirmation* Make(FString Code, FString Password, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EmailUpdateConfirmation", meta=(NativeBreakFunc))
	static void Break(const UEmailUpdateConfirmation* Serializable, FString& Code, FString& Password);
};