
#pragma once

#include "CoreMinimal.h"
#include "ServiceDependencyReference.h"

#include "ServiceDependencyReferenceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceDependencyReference To JSON String")
	static FString ServiceDependencyReferenceToJsonString(const UServiceDependencyReference* Serializable, const bool Pretty);		
};