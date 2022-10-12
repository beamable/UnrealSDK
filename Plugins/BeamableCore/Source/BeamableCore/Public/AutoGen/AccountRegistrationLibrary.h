
#pragma once

#include "CoreMinimal.h"
#include "AccountRegistration.h"

#include "AccountRegistrationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountRegistration To JSON String")
	static FString AccountRegistrationToJsonString(const UAccountRegistration* Serializable, const bool Pretty);		
};