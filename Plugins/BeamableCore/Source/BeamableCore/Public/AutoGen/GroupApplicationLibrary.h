
#pragma once

#include "CoreMinimal.h"
#include "GroupApplication.h"

#include "GroupApplicationLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupApplicationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupApplication To JSON String")
	static FString GroupApplicationToJsonString(const UGroupApplication* Serializable, const bool Pretty);		
};