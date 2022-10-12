

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "OptionalArrayOfGroupScoreBindingLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfGroupScoreBindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfGroupScoreBinding MakeOptionalArrayOfGroupScoreBinding(TArray<UGroupScoreBinding*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UGroupScoreBinding*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfGroupScoreBinding Conv_OptionalArrayOfGroupScoreBindingFromValue(TArray<UGroupScoreBinding*> Value);
};
