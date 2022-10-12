

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMailObjectMessage.h"

#include "OptionalMailObjectMessageLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMailObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMailObjectMessage MakeOptionalMailObjectMessage(UMailObjectMessage* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "MailObjectMessage To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMailObjectMessage Conv_OptionalMailObjectMessageFromValue(UMailObjectMessage* Value);
};
