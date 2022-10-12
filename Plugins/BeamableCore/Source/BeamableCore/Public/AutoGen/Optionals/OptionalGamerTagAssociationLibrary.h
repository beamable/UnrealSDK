

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalGamerTagAssociation.h"

#include "OptionalGamerTagAssociationLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalGamerTagAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalGamerTagAssociation MakeOptionalGamerTagAssociation(UGamerTagAssociation* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GamerTagAssociation To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalGamerTagAssociation Conv_OptionalGamerTagAssociationFromValue(UGamerTagAssociation* Value);
};
