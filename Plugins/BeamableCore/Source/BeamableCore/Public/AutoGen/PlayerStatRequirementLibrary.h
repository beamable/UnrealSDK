
#pragma once

#include "CoreMinimal.h"
#include "PlayerStatRequirement.h"

#include "PlayerStatRequirementLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerStatRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerStatRequirement To JSON String")
	static FString PlayerStatRequirementToJsonString(const UPlayerStatRequirement* Serializable, const bool Pretty);		
};