

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfMailObjectMessage.h"

#include "OptionalArrayOfMailObjectMessageLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfMailObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfMailObjectMessage MakeOptionalArrayOfMailObjectMessage(TArray<UMailObjectMessage*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UMailObjectMessage*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfMailObjectMessage Conv_OptionalArrayOfMailObjectMessageFromValue(TArray<UMailObjectMessage*> Value);
};
