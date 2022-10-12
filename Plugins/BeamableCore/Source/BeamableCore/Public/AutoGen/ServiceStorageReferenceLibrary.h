
#pragma once

#include "CoreMinimal.h"
#include "ServiceStorageReference.h"

#include "ServiceStorageReferenceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceStorageReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceStorageReference To JSON String")
	static FString ServiceStorageReferenceToJsonString(const UServiceStorageReference* Serializable, const bool Pretty);		
};