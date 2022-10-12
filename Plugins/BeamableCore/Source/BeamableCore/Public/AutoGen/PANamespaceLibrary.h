
#pragma once

#include "CoreMinimal.h"
#include "PANamespace.h"

#include "PANamespaceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPANamespaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PANamespace To JSON String")
	static FString PANamespaceToJsonString(const UPANamespace* Serializable, const bool Pretty);		
};