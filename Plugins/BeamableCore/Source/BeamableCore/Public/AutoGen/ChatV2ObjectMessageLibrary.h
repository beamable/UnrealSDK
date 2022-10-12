
#pragma once

#include "CoreMinimal.h"
#include "ChatV2ObjectMessage.h"

#include "ChatV2ObjectMessageLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UChatV2ObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ChatV2ObjectMessage To JSON String")
	static FString ChatV2ObjectMessageToJsonString(const UChatV2ObjectMessage* Serializable, const bool Pretty);		
};