
#pragma once

#include "CoreMinimal.h"
#include "PlayerStatus.h"

#include "PlayerStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerStatus To JSON String")
	static FString PlayerStatusToJsonString(const UPlayerStatus* Serializable, const bool Pretty);		
};