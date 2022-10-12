
#pragma once

#include "CoreMinimal.h"
#include "WebhookComet.h"

#include "WebhookCometLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UWebhookCometLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize WebhookComet To JSON String")
	static FString WebhookCometToJsonString(const UWebhookComet* Serializable, const bool Pretty);		
};