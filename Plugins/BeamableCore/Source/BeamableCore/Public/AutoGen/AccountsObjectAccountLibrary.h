
#pragma once

#include "CoreMinimal.h"
#include "AccountsObjectAccount.h"

#include "AccountsObjectAccountLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountsObjectAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountsObjectAccount To JSON String")
	static FString AccountsObjectAccountToJsonString(const UAccountsObjectAccount* Serializable, const bool Pretty);		
};