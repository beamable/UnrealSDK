
#pragma once

#include "CoreMinimal.h"
#include "CohortRequirement.h"

#include "CohortRequirementLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCohortRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CohortRequirement To JSON String")
	static FString CohortRequirementToJsonString(const UCohortRequirement* Serializable, const bool Pretty);		
};