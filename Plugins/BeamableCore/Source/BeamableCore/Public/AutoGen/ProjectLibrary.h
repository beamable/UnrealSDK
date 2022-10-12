
#pragma once

#include "CoreMinimal.h"
#include "Project.h"

#include "ProjectLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UProjectLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Project To JSON String")
	static FString ProjectToJsonString(const UProject* Serializable, const bool Pretty);		
};