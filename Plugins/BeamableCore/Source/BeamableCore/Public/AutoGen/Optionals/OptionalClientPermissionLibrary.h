

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"

#include "OptionalClientPermissionLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalClientPermissionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalClientPermission MakeOptionalClientPermission(UClientPermission* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ClientPermission To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalClientPermission Conv_OptionalClientPermissionFromValue(UClientPermission* Value);
};
