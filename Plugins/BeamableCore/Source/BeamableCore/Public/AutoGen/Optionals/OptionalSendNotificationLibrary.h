

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalSendNotification.h"

#include "OptionalSendNotificationLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalSendNotificationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalSendNotification MakeOptionalSendNotification(USendNotification* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "SendNotification To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalSendNotification Conv_OptionalSendNotificationFromValue(USendNotification* Value);
};
