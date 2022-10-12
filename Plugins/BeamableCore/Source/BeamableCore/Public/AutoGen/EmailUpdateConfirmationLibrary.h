
#pragma once

#include "CoreMinimal.h"
#include "EmailUpdateConfirmation.h"

#include "EmailUpdateConfirmationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEmailUpdateConfirmationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EmailUpdateConfirmation To JSON String")
	static FString EmailUpdateConfirmationToJsonString(const UEmailUpdateConfirmation* Serializable, const bool Pretty);		
};