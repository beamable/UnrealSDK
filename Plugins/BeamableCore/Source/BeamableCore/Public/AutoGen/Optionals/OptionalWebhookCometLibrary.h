

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalWebhookComet.h"

#include "OptionalWebhookCometLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalWebhookCometLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalWebhookComet MakeOptionalWebhookComet(UWebhookComet* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "WebhookComet To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalWebhookComet Conv_OptionalWebhookCometFromValue(UWebhookComet* Value);
};
