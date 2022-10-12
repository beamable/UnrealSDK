
#pragma once

#include "CoreMinimal.h"
#include "PasswordUpdateConfirmation.h"

#include "PasswordUpdateConfirmationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPasswordUpdateConfirmationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PasswordUpdateConfirmation To JSON String")
	static FString PasswordUpdateConfirmationToJsonString(const UPasswordUpdateConfirmation* Serializable, const bool Pretty);		
};