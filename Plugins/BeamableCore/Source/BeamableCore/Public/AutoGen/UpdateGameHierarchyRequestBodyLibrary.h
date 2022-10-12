
#pragma once

#include "CoreMinimal.h"
#include "UpdateGameHierarchyRequestBody.h"

#include "UpdateGameHierarchyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UUpdateGameHierarchyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize UpdateGameHierarchyRequestBody To JSON String")
	static FString UpdateGameHierarchyRequestBodyToJsonString(const UUpdateGameHierarchyRequestBody* Serializable, const bool Pretty);		
};