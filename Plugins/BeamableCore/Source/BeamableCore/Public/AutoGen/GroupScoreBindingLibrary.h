
#pragma once

#include "CoreMinimal.h"
#include "GroupScoreBinding.h"

#include "GroupScoreBindingLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupScoreBindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupScoreBinding To JSON String")
	static FString GroupScoreBindingToJsonString(const UGroupScoreBinding* Serializable, const bool Pretty);		
};