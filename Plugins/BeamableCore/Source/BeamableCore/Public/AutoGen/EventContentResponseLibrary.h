
#pragma once

#include "CoreMinimal.h"
#include "EventContentResponse.h"

#include "EventContentResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventContentResponse To JSON String")
	static FString EventContentResponseToJsonString(const UEventContentResponse* Serializable, const bool Pretty);		
};