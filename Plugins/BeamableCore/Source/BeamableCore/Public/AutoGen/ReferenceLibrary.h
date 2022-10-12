
#pragma once

#include "CoreMinimal.h"
#include "Reference.h"

#include "ReferenceLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Reference To JSON String")
	static FString ReferenceToJsonString(const UReference* Serializable, const bool Pretty);		
};