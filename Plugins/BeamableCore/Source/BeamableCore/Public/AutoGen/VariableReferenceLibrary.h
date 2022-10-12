
#pragma once

#include "CoreMinimal.h"
#include "VariableReference.h"

#include "VariableReferenceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UVariableReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize VariableReference To JSON String")
	static FString VariableReferenceToJsonString(const UVariableReference* Serializable, const bool Pretty);		
};