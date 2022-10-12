
#pragma once

#include "CoreMinimal.h"
#include "ListDefinitionsResponse.h"

#include "ListDefinitionsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListDefinitionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListDefinitionsResponse To JSON String")
	static FString ListDefinitionsResponseToJsonString(const UListDefinitionsResponse* Serializable, const bool Pretty);		
};