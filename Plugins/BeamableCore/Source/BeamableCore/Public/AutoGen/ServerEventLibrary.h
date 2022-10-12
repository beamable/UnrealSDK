
#pragma once

#include "CoreMinimal.h"
#include "ServerEvent.h"

#include "ServerEventLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServerEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServerEvent To JSON String")
	static FString ServerEventToJsonString(const UServerEvent* Serializable, const bool Pretty);		
};