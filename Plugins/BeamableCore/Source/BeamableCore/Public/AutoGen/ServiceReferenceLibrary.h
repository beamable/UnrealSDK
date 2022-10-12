
#pragma once

#include "CoreMinimal.h"
#include "ServiceReference.h"

#include "ServiceReferenceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceReference To JSON String")
	static FString ServiceReferenceToJsonString(const UServiceReference* Serializable, const bool Pretty);		
};