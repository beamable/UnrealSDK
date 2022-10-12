
#pragma once

#include "CoreMinimal.h"
#include "ItemArchetype.h"

#include "ItemArchetypeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UItemArchetypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ItemArchetype To JSON String")
	static FString ItemArchetypeToJsonString(const UItemArchetype* Serializable, const bool Pretty);		
};