
#pragma once

#include "CoreMinimal.h"
#include "SendMessageResponse.h"

#include "SendMessageResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMessageResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMessageResponse To JSON String")
	static FString SendMessageResponseToJsonString(const USendMessageResponse* Serializable, const bool Pretty);		
};