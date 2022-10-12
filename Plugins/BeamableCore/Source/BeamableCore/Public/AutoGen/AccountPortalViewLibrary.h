
#pragma once

#include "CoreMinimal.h"
#include "AccountPortalView.h"

#include "AccountPortalViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountPortalViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountPortalView To JSON String")
	static FString AccountPortalViewToJsonString(const UAccountPortalView* Serializable, const bool Pretty);		
};