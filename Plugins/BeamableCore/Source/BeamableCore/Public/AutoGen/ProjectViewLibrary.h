
#pragma once

#include "CoreMinimal.h"
#include "ProjectView.h"

#include "ProjectViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UProjectViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ProjectView To JSON String")
	static FString ProjectViewToJsonString(const UProjectView* Serializable, const bool Pretty);		
};