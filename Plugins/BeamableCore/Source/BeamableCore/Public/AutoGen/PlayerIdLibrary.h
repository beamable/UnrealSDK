
#pragma once

#include "CoreMinimal.h"
#include "PlayerId.h"

#include "PlayerIdLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerId To JSON String")
	static FString PlayerIdToJsonString(const UPlayerId* Serializable, const bool Pretty);		
};