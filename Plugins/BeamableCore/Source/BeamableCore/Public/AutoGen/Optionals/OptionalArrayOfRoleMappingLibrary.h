

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfRoleMapping.h"

#include "OptionalArrayOfRoleMappingLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfRoleMappingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfRoleMapping MakeOptionalArrayOfRoleMapping(TArray<URoleMapping*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<URoleMapping*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfRoleMapping Conv_OptionalArrayOfRoleMappingFromValue(TArray<URoleMapping*> Value);
};
