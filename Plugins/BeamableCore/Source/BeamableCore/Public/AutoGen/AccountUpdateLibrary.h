
#pragma once

#include "CoreMinimal.h"
#include "AccountUpdate.h"

#include "AccountUpdateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountUpdate To JSON String")
	static FString AccountUpdateToJsonString(const UAccountUpdate* Serializable, const bool Pretty);		
};