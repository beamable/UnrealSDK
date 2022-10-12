
#pragma once

#include "CoreMinimal.h"
#include "AccountsBasicAccount.h"

#include "AccountsBasicAccountLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountsBasicAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountsBasicAccount To JSON String")
	static FString AccountsBasicAccountToJsonString(const UAccountsBasicAccount* Serializable, const bool Pretty);		
};