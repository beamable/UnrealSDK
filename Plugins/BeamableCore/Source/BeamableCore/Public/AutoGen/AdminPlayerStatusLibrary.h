
#pragma once

#include "CoreMinimal.h"
#include "AdminPlayerStatus.h"

#include "AdminPlayerStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAdminPlayerStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AdminPlayerStatus To JSON String")
	static FString AdminPlayerStatusToJsonString(const UAdminPlayerStatus* Serializable, const bool Pretty);		
};