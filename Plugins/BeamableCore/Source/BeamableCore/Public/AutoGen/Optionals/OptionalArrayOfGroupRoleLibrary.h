

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupRole.h"

#include "OptionalArrayOfGroupRoleLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfGroupRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfGroupRole MakeOptionalArrayOfGroupRole(TArray<UGroupRole*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UGroupRole*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfGroupRole Conv_OptionalArrayOfGroupRoleFromValue(TArray<UGroupRole*> Value);
};
