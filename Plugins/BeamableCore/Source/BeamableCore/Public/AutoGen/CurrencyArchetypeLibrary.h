
#pragma once

#include "CoreMinimal.h"
#include "CurrencyArchetype.h"

#include "CurrencyArchetypeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCurrencyArchetypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CurrencyArchetype To JSON String")
	static FString CurrencyArchetypeToJsonString(const UCurrencyArchetype* Serializable, const bool Pretty);		
};